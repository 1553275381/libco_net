/* linux header */
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>  
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <endian.h>
#include <fcntl.h>
#include <sys/time.h>

/* c header */
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <string.h>

/* user defined header */
#include "co_thread.h"
#include "buffer.h"
#include "error.h"
#include "global.h"

/* pb */
#include "comm_basic.pb.h"

using namespace std;

#define OPEN_FD_LIMIT   10000       /* to configure */
#define PORT 			8888        /* to configure */
#define EPOLL_SIZE 		1024        /* to configure */
#define LISTEN_SIZE 	256         /* to configure */
#define TIME_OUT 		3           /* to configure */
#define STRING_EOF      '\0'
#define CLRF            "\r\n"

#define READ_EVENT 		(1 << 0)
#define WRITE_EVENT 	(1 << 1)

#define MASTER          (1 << 0) /* master 实例 */
#define SLAVE           (1 << 1) /* slave  实例 */

#define IPV4_MASK       (1 << 0)
#define IPV6_MASK       (1 << 1)

// #define gettid() syscall(SYS_gettid)  

#define RETURN_CHECK(RET) \
	if(0 != RET) return RET;

//类型声明
typedef class log				log_t;
typedef struct timer_s			mtimer_t;
typedef struct event_s			event_t;
typedef class buffer			buffer_t;
typedef struct connection_s		connection_t;
typedef struct cycle_s			cycle_t;

typedef list<event_t*>::iterator event_pos;
typedef list<event_t*>			io_task_queue_t;
typedef list<event_t*>			accept_task_queue_t;
typedef list<connection_t*>		client_free_list_t; //智能指针
typedef set<connection_t*>		client_set_t;    //智能指针
typedef vector<struct  epoll_event>		epoll_event_vec_t;
typedef map<uint64_t,  set<mtimer_t*>>	timer_queue_t;

//函数指针
typedef int (*event_handler_t)(connection_t *);
typedef void (*timer_func_t)(void *);

//函数声明
void del_event_timer(cycle_t* cycle, event_t* ev);
void conn_time_out(void *);
void add_event_timer(cycle_t* cycle, uint32_t after, uint32_t every, timer_func_t func, event_t* ev);

/*  todo 
 *  accept 解析对端 ip:port，协议类型
 *  安装信号机制
 *  限制描述符分配
 *  connection_t 兼容 timer
 *  connection_t 兼容 stop
 *  cycle_t 兼容 stop
 *  完善master流程，兼容子进程通信，子进程死后拉起
		1) 子进程死，master进程拉起
		2) master进程死，所有子进程抢夺文件锁，抢夺的那个拉起master进程
		3) master定时器每 10ms 监听所有子进程健康
		4) 每个子进程定时器监听 master 进程健康
 *  添加 mysql 访问器，兼容协程
 *  添加 redis 访问器，兼容协程
 *  添加配置解析
 *  防止惊群
 *  扩展成 c++ */

//--------------------------------------------------------------------------------

/* bug:
 *  1. 高并发请求服务的时候，有若干连接处于 CLOSE_WAIT 状态，说明服务没把套接字关闭掉  [已解决 - √]
 *  2. 内存泄漏 bug  [已解决 - √]
 *  3. 定时器统一时间添加多个只能执行一个  [已解决 - √] */

typedef struct timer_s
{
	void* handler;
	void* arg;
} mtimer_t;

/* 读写事件结构体 */
typedef struct event_s
{
	event_handler_t handler; /* 事件handler */
	void* arg;             /* handler参数 */
	int mask;            /* 事件类型，READ_EVENT or WRITE_EVENT */
	int timer_set:1;     /* 是否设置定时器 */
	int timeout:1;       /* 是否超时 */
	mtimer_t timer;        /* 定时器 */
	int posted:1;          /* 是否放入了任务队列 */
	event_pos pos;
} event_t;

typedef struct ip_addr
{
	string  ip;
	int     port;
	int     family:2; /* ipv4 还是 ipv6 */
} ip_addr;

/* 客户端请求完整请求体 */
typedef struct request_s
{
	connection_t* c;
	void* data;
} request_t;

/* 客户端请求完整请求体 */
typedef struct response_s
{
	connection_t* c;
	void* data;
} response_t;

/* 客户端链接 */
typedef struct connection_s
{
	int fd;			         /* 套接字 */
	int mask;                /* 事件类型掩码 */
	
	ip_addr local_addr;      /* 本地地址 */
	ip_addr peer_addr;       /* 对端地址 */

	buffer_t in_buf;         /* 网络包读缓冲区 */
	buffer_t out_buf;        /* 网络包写缓冲区 */

	request_t req;           /* 请求体 */
	response_t resp;         /* 应答体 */

	event_t rev;	         /* 读事件 */
	event_t wev;	         /* 写事件 */

	cycle_t* cycle;        /* 对应的事件循环结构体 */

	// int timer:1;             /* 是否已加入到定时器队列中 */
	int active:1; 	         /* 链接是否已加入epoll队列中 */
	int accept:1; 	         /* 是否用于监听套接字 */
	int ready:1;  	         /* 第一次建立链接是否有开始数据，没有则不建立请求体 */
	int closing:1;           /* 半关半闭，客户端已经close了，而此时服务端有数据未发送完 */
	int stop:1;              /* 删除连接用到的标记位 */
} connection_t;

/* 事件循环体 */
typedef struct cycle_s
{
	int   					efd;           		/* epoll fd */
	int   					lfd;           		/* listen fd，暂时放在 cycle_t 里，之后放在 server 里 */
	uint64_t 				now;        		/* 本地时间 */
	client_set_t            cli_set;           	/* 用户字典 */
	client_free_list_t      conn_free;          	/* 空闲连接 */
	timer_queue_t 			timer_queue;       	/* 定时器存储队列 */
	io_task_queue_t 		io_task_queue;     	/* epoll 激活事件: IO 网络读写事件任务队列 */
	accept_task_queue_t 	accept_task_queue; 	/* epoll 激活事件: accept 任务队列 */
	epoll_event_vec_t       ee_vec;            	/* 存储所有 epoll 注册事件 */
	sig_atomic_t 			stop:1;          	/* 是否停止 */
} cycle_t;

typedef struct server
{
	pid_t     pid;           /* 进程pid */
	int       port;          /* 绑定端口 */
	int       open_fd_limit; /* 进程打开fd最大数，默认值 10000 */
	char*     conf_path;     /* 配置文件 */
	char*     log_path;      /* 日志文件 */
	// log_t*    log_p;         /* 日志，智能指针 */
	cycle_t*  cycle;       /* 事件循环结构体，智能指针 */
	char*     bind_addr[16]; /* 端口绑定的本地IP列表 */
	int*      bind_count;    /* 实际绑定本地IP列表数( <= 16) */
	int       daemonize:1;   /* 是否后台模式 */
	int       type;          /* bitwise, server类型，eg: master or slave */
	int       unix_fd;       /* UNIX 域套接字 */
	char*     unix_path;     /* 路径: /tmp/happy.sock */
	int       cpu_num;       /* cpu核数 */
} server;

server  ser;

int set_fd_noblock(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	flags |= O_NONBLOCK;

	int ret = fcntl(fd, F_SETFL, flags);
	if(0 != ret)
	{
		info_log("set fd noblock failed, errno msg:[%s]\n", strerror(errno));
		return -1;
	}

	return 0;
}

int set_fd_cloexec(int fd)
{
	int flags = fcntl(fd, F_GETFD, 0);
	flags |= FD_CLOEXEC;

	int ret = fcntl(fd, F_SETFD, flags);
	if(0 != ret)
	{
		info_log("set fd cloexec failed, errno msg:[%s]\n", strerror(errno));
		return -1;
	}

	return 0;
}

/* 1. so_reuseaddr 允许处于[time_wait]的socket重复可用
 * 2. 允许同一端口绑定多个实例，只要每个实例绑定本地ip地址不同即可
 * 3. 允许统一进程绑定同一个端口多个套接口，只要每个套接口指定不同IP即可 */
int set_fd_reuseaddr(int fd)
{
	int yes = 1;

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&yes, sizeof(yes)) == -1)
    {
    	info_log("set reuseaddr failed, errno msg:[%s]\n", strerror(errno));
        return -1;
    }

	return 0;
}

/* 1. 允许重复绑定，但 bind 相同 ip，port 的套接口都指定该选项才行 */
int set_fd_reuseport(int fd)
{
	int yes = 1;

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, (const void *)&yes, sizeof(yes)) == -1)
    {
    	info_log("set reuseport failed, errno msg:[%s]\n", strerror(errno));
        return -1;
    }

	return 0;
}

int set_fd_noblock_and_cloexec(int fd)
{
	if(set_fd_noblock(fd) != 0 ||
		set_fd_cloexec(fd) != 0)
	{
		info_log("set fd noblock & cloexec failed, errno msg:[%s]\n", strerror(errno));
		return -1;
	}

	return 0;
}

int read_handler(connection_t* c);
int write_handler(connection_t* c);

int empty_handler(connection_t* c)
{
	info_log("fd:%d empty_handler\n", c->fd);
	return 0;
}

/* 添加epoll事件，mask为bitwise，可以兼容 READ_EVENT，WRITE_EVENT  */
int epoll_add_event(connection_t* c, int ep_fd, int sock_fd, int mask)
{
	int ret     = 0;
	int op      = c->active ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;
	struct epoll_event ee = {0};

	// mask |= c->mask;
	if(mask & READ_EVENT)  ee.events |= EPOLLIN | EPOLLET | EPOLLRDHUP;
	if(mask & WRITE_EVENT) ee.events |= EPOLLOUT;
	ee.data.ptr = (void *) c;

	// info_log("[%s] ep_fd:%d sock_fd:%d c->active:%d\n", __func__, ep_fd, sock_fd, c->active);

	ret = epoll_ctl(ep_fd, op, sock_fd, &ee);
	if(0 != ret) 
	{
		info_log("[%s:%d] | errno msg:%s \n", 
			__func__, __LINE__, strerror(errno));
		return -1;
	}

	c->active = 1;

	return 0;
}

int epoll_delete_event(connection_t* c, int ep_fd, int sock_fd, int del_mask)
{
	int ret = 0;
	int op  = EPOLL_CTL_DEL;
	struct epoll_event ee = {0};

	// del_mask |= c->mask;
	if(del_mask & READ_EVENT)  ee.events |= EPOLLIN | EPOLLET | EPOLLRDHUP;
	if(del_mask & WRITE_EVENT) ee.events |= EPOLLOUT;

	ret = epoll_ctl(ep_fd, op, sock_fd, &ee);
	if(0 != ret)
	{
		info_log("method:[%s] line:[%d] | errno msg:%s \n", 
			__func__, __LINE__, strerror(errno));
		return -1;
	}

	if(del_mask & READ_EVENT & WRITE_EVENT)
	{
		c->active = 0;	
	}

	return 0;
}

int epoll_add_listen(connection_t* c, int ep_fd, int listen_fd)
{
	int ret = 0;
	struct epoll_event ee = {0};
	ee.events = EPOLLIN;
	ee.data.ptr = c;

	ret = epoll_ctl(ep_fd, EPOLL_CTL_ADD, listen_fd, &ee);
	if(0 != ret)
	{
		info_log("method:[%s] line:[%d] | errno msg:%s \n", 
			__func__, __LINE__, strerror(errno));
		return -1;
	}

	return 0;
}

int epoll_del_listen(connection_t* c, int ep_fd, int listen_fd)
{
	int ret = 0;
	struct epoll_event ee = {0};
	ee.events = EPOLLIN;
	ee.data.ptr = c;

	ret = epoll_ctl(ep_fd, EPOLL_CTL_DEL, listen_fd, &ee);
	if(0 != ret)
	{
		info_log("method:[%s] line:[%d] | errno msg:%s \n", 
			__func__, __LINE__, strerror(errno));
		return -1;
	}

	return 0;
}

connection_t* get_connection(cycle_t* cycle)
{
	connection_t* c = cycle->conn_free.front();
	cycle->conn_free.pop_front();
	return c;
}

/* 一个稍微复杂的过程 */
int free_connection(connection_t* c)
{
	printf("free_connection fd:%d\n", c->fd);
	cycle_t* cycle = c->cycle;
	int efd 	     = cycle->efd;
	int fd           = c->fd;

	if(-1 == fd) return 0;

	/* 从字典里删除 */
	cycle->cli_set.erase(c);

	/* 空闲连接回收结点 */
	cycle->conn_free.push_back(c);

	/* 1. 删除读写事件 */
	c->rev.handler = empty_handler;
	c->wev.handler = empty_handler;

	epoll_delete_event(c, efd, fd, READ_EVENT|WRITE_EVENT);

	/* 1. 删除 读/写 事件定时器 */
	if(c->rev.timer_set) 
	{
		del_event_timer(cycle, &(c->rev));
	}

	if(c->wev.timer_set)
	{
		del_event_timer(cycle, &(c->wev));
	}

	/* 2. 删除 读/写 IO事件 post 队列 */
	if(c->rev.posted)
	{
		c->rev.posted = 0;
		cycle->io_task_queue.erase(c->rev.pos);
	}

	if(c->wev.posted)
	{
		c->wev.posted = 0;
		cycle->io_task_queue.erase(c->wev.pos);
	}

	/* . close fd */
	close(fd);
	c->fd = -1;

	return 0;
}

int accept_handler(connection_t* lc)
{
	/* 如果是监听事件，优先处理 */
	int ret = 0;
	cycle_t* cycle = lc->cycle;
	int efd 	     = cycle->efd;

	struct sockaddr_in ca;
	socklen_t len = sizeof(ca);

	int fd = 0;
	while((fd = accept4(cycle->lfd, (sockaddr *)&ca, &len, SOCK_NONBLOCK)) > 0)
	{
		// info_log("loc:[%s] line:[%d]  accept fd:%d\n", __func__, __LINE__, fd);
		connection_t* p_conn = get_connection(cycle);
		if(NULL == p_conn)
		{
			close(fd);
			continue;
		}
		p_conn->fd		= fd;
		// p_conn->timer   = 0;
		p_conn->active	= 0;
		p_conn->accept	= 0;
		p_conn->ready   = 0;
		p_conn->stop 	= 0;

		//读事件
		event_t* rev    = &(p_conn->rev);
		rev->handler    = read_handler;
		rev->arg 	    = p_conn;
		rev->mask       = READ_EVENT;
		rev->timer_set  = 0;
		rev->timeout    = 0;
		rev->posted 	= 0;
		// rev->timer.handler = 
		//写事件
		event_t* wev    = &(p_conn->wev);
		wev->handler    = empty_handler;
		wev->arg 	    = p_conn;
		wev->mask       = WRITE_EVENT;
		wev->timer_set  = 0;
		wev->timeout    = 0;
		wev->posted 	= 0;

		p_conn->cycle = cycle;

		ret = set_fd_reuseaddr(fd);
		if(0 != ret)
		{
			info_log("listen fd set reuseaddr failed, errno msg:%s\n", strerror(errno));
			return -1;
		}

		epoll_add_event(p_conn, efd, p_conn->fd, READ_EVENT);

		/* 加入到 cli_set 里 */
		if(cycle->cli_set.find(p_conn) == cycle->cli_set.end())
		{
			cycle->cli_set.insert(p_conn);
		} 
		else 
		{
			err_log("create connection error");
			exit(-1);
		}

		add_event_timer(cycle, 3000, 0, conn_time_out, rev);
	}

	return 0;
}

/* 解析buffer，直到解析完整请求 */
int protocol_decoder(connection_t* c, int& err)
{
	buffer_t& in_buffer = c->in_buf;
	char* eof = in_buffer.find_eof(CLRF);
	if(!eof)
	{
		err = kDECODER_AGAIN;
		return -1;
	}

	return eof - in_buffer.read_begin();
}

/* 协议解析 */
int parse_protocol_handler(connection_t* c)
{
	int ret = 0;
	int err = 0;
	buffer_t& in_buffer = c->in_buf;
	ret = protocol_decoder(c, err);
	if(0 != ret)
	{
		if(kDECODER_AGAIN == err)
		{
			return kDECODER_AGAIN;
		}
	}

	/* 解析出完整的请求 */
	char buf[ret+1];
	buf[ret] = '\0';
	in_buffer.get_string(ret, buf);
	in_buffer.read_len(strlen(CLRF));

	common::comm_request* req = new common::comm_request();
	req->ParseFromString(buf);
	c->req.data = req;

	return 0;
}

/* 业务处理函数 */
int client_handler(connection_t* c)
{
	buffer_t& out_buf = c->out_buf;

	/* ab test */
	// const char* str = "HTTP/1.1 200 OK\r\nServer: Tengine/2.2.2\r\nDate: Tue, 17 Jul 2018 03:02:21 GMT\r\nContent-Type: text/html\r\nContent-Length: 17\r\nConnection: keep-alive\r\n\r\njiabo 123456798\r\n";
	// out_buf.append_string(str);
	
	/* 客户端 test */
	// common::comm_request req;
	// req.CopyFrom(*(common::comm_request*)c->req.data);
	common::comm_request* req = (common::comm_request*)c->req.data;
	printf("---------- read ----------\n");
	req->PrintDebugString();
	
	common::comm_response resp;
	resp.mutable_head()->set_err_code(1);
	resp.mutable_head()->set_err_msg("ok");
	string tmp = req->body();
	reverse(begin(tmp), end(tmp));
	resp.set_body("=== " + tmp + " ===");
	string str;
	resp.SerializeToString(&str);
	out_buf.append_string(str.c_str());
	out_buf.append_string(CLRF);

	delete req;
	
	return 0;
}

int read_handler(connection_t* c)
{
	cycle_t* cycle 	= c->cycle;
	int efd 	     	= cycle->efd;
	event_t* rev     	= &c->rev;
	buffer_t& in_buffer = c->in_buf;
	buffer_t& out_buf   = c->out_buf;

	int fd = c->fd;
	int ret = 0;
	int err = 0;

	if(rev->timeout) 
	{
		ret = 0;
		goto error;
	}

	if(c->stop)
	{
		ret = 0;
		goto error;
	}

	ret = in_buffer.read_buf(fd, err);
	if(ret < 0)
	{
		if(err == kBUFFER_EAGAIN) /* 数据读取错误 */
		{
			ret = kBUFFER_EAGAIN;
		}
		
		/* kBUFFER_ERROR 其他错误直接释放链接 */
		info_log("buf read error, ret:[%d] errno msg:[%s]\n", ret, strerror(errno));
		
		ret = -1;
		goto error;	
	}

	if(err == kBUFFER_EOF) /* 客户端关闭 */
	{
		ret = 0;
		goto error;
	}

	ret = parse_protocol_handler(c);
	if(kDECODER_ERROR == ret)
	{
		ret = -1;
		goto error;
	}
	else if(kDECODER_AGAIN == ret)
	{
		ret = 0;
	}

	client_handler(c);

	// info_log("========>  buf_len:%d, buf:%s\n", out_buf.readable_size(), out_buf.read_begin());
	ret = out_buf.write_buf(fd, err);
	if(ret < 0 && err == kBUFFER_ERROR)
	{
		ret = -1;
		goto error;
	}
	// info_log("write has_write:%d unwrite:%d\n", ret, out_buf.readable_size());
	if(out_buf.readable_size() > 0)
	{
		epoll_add_event(c, efd, fd, WRITE_EVENT);
		c->wev.handler = write_handler;
	}
	else
	{
		/* 如果（没有定时器，没有buf么写完的，没有buf要读的，则调用这个，否则设置stop为1）*/
		c->stop = 1;
		//否则
		goto error;
	}

error:
	free_connection(c);

	return ret;
}

int write_empty_handler(connection_t* c)
{
	info_log("%s\n", "write_empty_handler");
	return 0;
}

/* 执行用户请求后，开始对客户端写数据，若写不完，则开始对写事件设置write_handler 
   如果写完以后，要置 write_handler 为 emtpy_handler，否则有可能写事件再次触发 */
int write_handler(connection_t* c)
{
	int ret       = 0;
	int err       = 0;
	int fd        = c->fd;
	event_t* wev  = &c->rev;

	if(wev->timeout) 
	{
		free_connection(c);
		return 0;
	}

	buffer_t& out_buf = c->out_buf;
	ret = out_buf.write_buf(fd, err);
	// info_log("[%s->%s:%d] unwrite:%d\n", __FILE__, __func__, __LINE__, out_buf.readable_size());
	if(out_buf.readable_size() == 0)
	{
		c->wev.handler = write_empty_handler;
		free_connection(c);
	}

	return ret;
}

static uint64_t get_curr_msec()
{
	uint64_t msec;
	struct timeval tv;

	int ret = gettimeofday(&tv, 0);
	if(0 != ret)
	{
		return -1;
	}

    msec = tv.tv_sec * 1000 + tv.tv_usec / 1000;

	return msec;
}

typedef struct timer_arg
{
	timer_func_t func;
	void* arg;
	void* ctx;
	uint32_t every;
	uint64_t when;
} timer_arg_t;

/* 间隔定时器执行 func
 * 1. 执行 func
 * 2. 重新计算定时器，再次插入 func */
void timer_func(void* arg)
{
	timer_arg_t* t_arg = static_cast<timer_arg_t*>(arg);

	// timer_func_t func = t_arg->func;
	// void* func_arg  = t_arg->arg;
	((event_handler_t)t_arg->func)((connection_t *)t_arg->arg);

	if(0 == t_arg->every) 
	{
		delete t_arg;
		return;
	}

	cycle_t* cycle = (cycle_t *)t_arg->ctx;
	uint64_t when = cycle->now + t_arg->every;
	t_arg->when = when;

	mtimer_t* t = new mtimer_t;
	t->handler = (void*)timer_func;
	t->arg     = (void*)t_arg;
	cycle->timer_queue[when].insert(t);
}

/* 1. after: 几毫秒以后执行
 * 2. every: 每个几毫秒周期性执行一次
 * 3. func:  执行函数
 * 4. arg:   函数参数 */
mtimer_t* add_timer(cycle_t* cycle, uint64_t after, uint32_t every, timer_func_t func, const void* arg)
{
	uint64_t when = cycle->now + after;

	timer_arg_t* t_arg = new timer_arg_t;
	t_arg->func  = func;
	t_arg->arg   = const_cast<void*>(arg);
	t_arg->ctx   = cycle;
	t_arg->every = every;
	t_arg->when  = when;

	mtimer_t* t = new mtimer_t;
	t->handler = (void*)timer_func;
	t->arg     = (void*)t_arg;

	cycle->timer_queue[when].insert(t);

	return t;
}

void del_timer(cycle_t* cycle, mtimer_t* t)
{
	if(t == nullptr) return;

	timer_arg_t* t_arg = static_cast<timer_arg_t*>(t->arg);

	timer_queue_t::iterator it = cycle->timer_queue.find(t_arg->when);
	if (it == cycle->timer_queue.end()) return;

	cycle->timer_queue.erase(it);

	if(t_arg->every > 0) delete t_arg;
}

void add_event_timer(cycle_t* cycle, uint32_t after, uint32_t every, timer_func_t func, event_t* ev)
{
	ev->timer_set = 1;
	add_timer(cycle, after, every, func, (void *)ev);
}

void del_event_timer(cycle_t* cycle, event_t* ev)
{
	ev->timer_set = 0;
	del_timer(cycle, &(ev->timer));
}

void conn_time_out(void* arg)
{
	event_t* rev = static_cast<event_t *>(arg);;
	connection_t* c = static_cast<connection_t *>(rev->arg);
	if(!c->ready) free_connection(c);
}

void tmp_timer(void* arg)
{
	printf("%s\n", (const char*)arg);
}

void del_timer_test(void* arg)
{
	mtimer_t* t = static_cast<mtimer_t *>(arg);
	timer_arg_t* t_arg = static_cast<timer_arg_t*>(t->arg);
	del_timer((cycle_t*)t_arg->ctx, t);
}

static int work_process_cycle(cycle_t* cycle)
{
	int ret = 0;
	int cnt = 0;
	int64_t time_out = -1;
	
	timer_queue_t& timer_queue             = cycle->timer_queue;
	io_task_queue_t& io_task_queue         = cycle->io_task_queue;
	accept_task_queue_t& accept_task_queue = cycle->accept_task_queue;
	epoll_event_vec_t& ee_vec              = cycle->ee_vec;

	pid_t id = gettid();
	// info_log("work process id:%d\n", id);
	/* todo 子进程搞事情 */
	int efd = epoll_create1(0);

	// cycle.lfd = lfd;
	cycle->efd = efd;

	connection_t* p_conn = new connection_t();
	// p_conn->id = -1;
	p_conn->fd = cycle->lfd;
	p_conn->rev.handler = accept_handler;
	p_conn->rev.arg = p_conn;

	p_conn->wev.handler = empty_handler;
	p_conn->wev.arg = NULL;

	p_conn->cycle = cycle;
	p_conn->accept = 1;

	ret = epoll_add_listen(p_conn, efd, p_conn->fd);
	if(0 != ret)
	{
		info_log("listen fd epoll_add failed\n");
		return -1;
	}

	cycle->now = get_curr_msec();

	/* 定时器逻辑，已隐去，若开启去掉注释即可 */
	// add_timer(cycle, 1000, 1000, tmp_timer, "every 1 second");
	// add_timer(cycle, 5000, 5000, tmp_timer, "every 5 second");
	// add_timer(cycle, 1000, 0, tmp_timer, "1 second later");
	// add_timer(cycle, 3000, 0, tmp_timer, "3 second later");
	// add_timer(cycle, 5000, 0, tmp_timer, "5 second later");

	// mtimer_t* t4 = add_timer(cycle, 4000, 0, tmp_timer, "4 second later");
	// add_timer(cycle, 2000, 0, del_timer_test, t4);
	//重复删除
	// add_timer(cycle, 4000, 0, del_timer_test, t4);

	while(1)
	{
		/* 进程退出 */
		if(cycle->stop)
		{
			//todo
		}

		/* -------------- 定时器 解析 -------------- */
		time_out = -1;
		timer_queue_t::iterator timer = timer_queue.lower_bound(cycle->now);
		if(timer != timer_queue.end())
		{
			time_out = timer->first - cycle->now;
		}

		/* -------------- epoll_wait -------------- */
		cnt = epoll_wait(efd, &*(ee_vec.begin()), ee_vec.size(), time_out);

		cycle->now = get_curr_msec();

		if(cnt == ee_vec.size())
		{
			ee_vec.resize(ee_vec.size() * 2);
		}

		for (int i = 0; i < cnt; ++i)
		{
			struct epoll_event* ee 	= &ee_vec[i];
			uint events 		    = ee->events;
			connection_t* c 		= (connection_t *)ee->data.ptr;
			int fd 					= c->fd;

			if(events & EPOLLRDHUP)
			{
				free_connection(c);
				
				continue;
			}

			if(events & EPOLLIN)
			{
				if(!c->ready)
				{
					c->ready = 1;
				}

				if(c->accept)
				{
					c->rev.pos = accept_task_queue.insert(accept_task_queue.end(), &(c->rev));
					c->rev.posted = 1;
				}
				else
				{
					//加入读事件队列
					c->rev.pos = io_task_queue.insert(io_task_queue.end(), &(c->rev));
					c->rev.posted = 1;
				}
			}
			
			if(events & EPOLLOUT)
			{
				/* 加入写事件队列 */
				c->wev.pos = io_task_queue.insert(io_task_queue.end(), &(c->wev));
				c->wev.posted = 1;
			}
		}

		/* -------------- accept 事件 -------------- */
		while(!accept_task_queue.empty())
		{
			event_t* ev = accept_task_queue.front();
			accept_task_queue.pop_front();
			ev->posted = 0;
			((event_handler_t)ev->handler)((connection_t *)ev->arg);
		}

		/* -------------- 定时器事件 -------------- */
		while(timer != timer_queue.end() && timer->first <= cycle->now) {

			for_each(timer->second.begin(), timer->second.end(), [](mtimer_t* t)
			{
				((event_handler_t)t->handler)((connection_t *)t->arg);
				delete t;
			});

			timer_queue.erase(timer++);
		}
		
		/* -------------- 网络 I/O 的读写事件 -------------- */
		while(!io_task_queue.empty())
		{
			event_t* ev = io_task_queue.front();
			io_task_queue.pop_front();
			ev->posted = 0;
			((event_handler_t)ev->handler)((connection_t *)ev->arg);
		}
	}

	return 0;
}

static int daemonize()
{
	int fd;
	
	if(0 != fork()) exit(0); /* parent exit */
	setsid(); /* create a new session */

	/* /dev/null是一个无底洞，丢弃一切写入的任何东西，读取它会返回一个EOF */
	if((fd = open("/dev/null", O_RDWR, 0)) != -1)
	{
		/* dup2 为 /dev/null 指定的描述符fd创建副本，并由newfd指定编号
		 * 以下说明，fd 由标准输入，标准输出，标准错误输出三个 fd 指定其副本编号，这意味着之后的输入输出都将丢进"垃圾桶"里
		 * 调用成功后，STDIN_FILENO，STDOUT_FILENO，STDERR_FILENO都指向了 /dev/null */
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		if (fd > STDERR_FILENO) close(fd);
	}
}

static int master_process_cycle(cycle_t* cycle)
{
	pid_t id = gettid();
	info_log("master process id:%d\n", id);
	close(cycle->lfd);
	info_log("master close lfd\n");
	/* todo master搞事情 */
	while(1)
	{
		sleep(3);
		// info_log("master_process_cycle %d\n", id);
	}
	
	return 0;
}

/* 安装信号 handler */
static void init_signal()
{
	
}

static void init_log()
{
	// ser.log_p = new log_t();
	// ser.log_p->set_log_path("ser.log");
}

static int init_ser(cycle_t* cycle)
{
	int ret  = 0;
	pid_t id = gettid();

	init_log();
	init_signal();
	
	client_free_list_t& conn_free = cycle->conn_free;
	// for_each(conn_free.begin(), conn_free.end(), [& conn_free]()
	// {
	// 	conn_free.push_back(new connection_t);
	// });
	for(int i = 0; i < 1024; i++)
	{
		conn_free.push_back(new connection_t);
	}

	cycle->ee_vec.resize(EPOLL_SIZE); /* 调节size */
	cycle->lfd = socket(AF_INET, SOCK_STREAM, 0);
	cycle->stop = 0;

	ret = set_fd_reuseaddr(cycle->lfd);
	if(0 != ret)
	{
		info_log("listen fd set reuseaddr failed, errno msg:%s\n", strerror(errno));
		return -1;
	}

    ret = set_fd_noblock(cycle->lfd);
	if(0 != ret)
	{
		info_log("set lfd[%d] failed\n", cycle->lfd);
		exit(ret);
	}

	struct sockaddr_in addr;

	bzero(&(addr.sin_zero), 8);

   	addr.sin_family 		= AF_INET;
	addr.sin_port 			= htons(PORT);
	addr.sin_addr.s_addr   	= INADDR_ANY;
	
	ret = bind(cycle->lfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
	if(0 != ret)
	{
		info_log("process[%d] bind lfd[%d] failed, errno msg:[%s]\n", id, cycle->lfd, strerror(errno));
		exit(ret);
	}

	info_log("process[%d] bind lfd[%d] sucess\n", id, cycle->lfd);

	ret = listen(cycle->lfd, LISTEN_SIZE);
	if(0 != ret)
	{
		info_log("process[%d] listen lfd[%d] failed\n", id, cycle->lfd);
		exit(ret);
	}

	// info_log("process[%d] listen lfd[%d] sucess\n", id, cycle.lfd);
	return 0;
}

int main(int argc, char* argv[])
{
	cycle_t cycle;

	RETURN_CHECK(init_ser(&cycle));

	int cpu_num = sysconf(_SC_NPROCESSORS_CONF);
	// info_log("cpu_num=%d\n", cpu_num);

	/* 为方便调试work进程，暂时先把work进程逻辑放在main流程上 */

	// for (int i = 0; i < cpu_num; ++i)
	// {
	// 	pid_t pid = fork();
	// 	switch(pid)
	// 	{
	// 		case -1:
	// 			info_log("fork error!\n");
	// 			break;
	// 		case 0:
	// 			/* 子进程 */
	// 			work_process_cycle();
	// 			return 0;
	// 		default:
	// 			break;
	// 	}
	// }

	/* 主进程 */
	// master_process_cycle(&cycle);

	/* 后台进程 */
	// daemonize();
	
	work_process_cycle(&cycle);
	
	return 0;
}