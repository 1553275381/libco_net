// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: comm_basic.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_comm_5fbasic_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_comm_5fbasic_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3007001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_comm_5fbasic_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_comm_5fbasic_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[4]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_comm_5fbasic_2eproto;
namespace common {
class comm_req;
class comm_reqDefaultTypeInternal;
extern comm_reqDefaultTypeInternal _comm_req_default_instance_;
class comm_request;
class comm_requestDefaultTypeInternal;
extern comm_requestDefaultTypeInternal _comm_request_default_instance_;
class comm_resp;
class comm_respDefaultTypeInternal;
extern comm_respDefaultTypeInternal _comm_resp_default_instance_;
class comm_response;
class comm_responseDefaultTypeInternal;
extern comm_responseDefaultTypeInternal _comm_response_default_instance_;
}  // namespace common
PROTOBUF_NAMESPACE_OPEN
template<> ::common::comm_req* Arena::CreateMaybeMessage<::common::comm_req>(Arena*);
template<> ::common::comm_request* Arena::CreateMaybeMessage<::common::comm_request>(Arena*);
template<> ::common::comm_resp* Arena::CreateMaybeMessage<::common::comm_resp>(Arena*);
template<> ::common::comm_response* Arena::CreateMaybeMessage<::common::comm_response>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace common {

// ===================================================================

class comm_req :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:common.comm_req) */ {
 public:
  comm_req();
  virtual ~comm_req();

  comm_req(const comm_req& from);
  comm_req(comm_req&& from) noexcept
    : comm_req() {
    *this = ::std::move(from);
  }

  inline comm_req& operator=(const comm_req& from) {
    CopyFrom(from);
    return *this;
  }
  inline comm_req& operator=(comm_req&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const comm_req& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const comm_req* internal_default_instance() {
    return reinterpret_cast<const comm_req*>(
               &_comm_req_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(comm_req* other);
  friend void swap(comm_req& a, comm_req& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline comm_req* New() const final {
    return CreateMaybeMessage<comm_req>(nullptr);
  }

  comm_req* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<comm_req>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const comm_req& from);
  void MergeFrom(const comm_req& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(comm_req* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "common.comm_req";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_comm_5fbasic_2eproto);
    return ::descriptor_table_comm_5fbasic_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 ver = 1;
  bool has_ver() const;
  void clear_ver();
  static const int kVerFieldNumber = 1;
  ::PROTOBUF_NAMESPACE_ID::int32 ver() const;
  void set_ver(::PROTOBUF_NAMESPACE_ID::int32 value);

  // optional int32 cmd = 2;
  bool has_cmd() const;
  void clear_cmd();
  static const int kCmdFieldNumber = 2;
  ::PROTOBUF_NAMESPACE_ID::int32 cmd() const;
  void set_cmd(::PROTOBUF_NAMESPACE_ID::int32 value);

  // optional int32 sub_cmd = 3;
  bool has_sub_cmd() const;
  void clear_sub_cmd();
  static const int kSubCmdFieldNumber = 3;
  ::PROTOBUF_NAMESPACE_ID::int32 sub_cmd() const;
  void set_sub_cmd(::PROTOBUF_NAMESPACE_ID::int32 value);

  // @@protoc_insertion_point(class_scope:common.comm_req)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::int32 ver_;
  ::PROTOBUF_NAMESPACE_ID::int32 cmd_;
  ::PROTOBUF_NAMESPACE_ID::int32 sub_cmd_;
  friend struct ::TableStruct_comm_5fbasic_2eproto;
};
// -------------------------------------------------------------------

class comm_resp :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:common.comm_resp) */ {
 public:
  comm_resp();
  virtual ~comm_resp();

  comm_resp(const comm_resp& from);
  comm_resp(comm_resp&& from) noexcept
    : comm_resp() {
    *this = ::std::move(from);
  }

  inline comm_resp& operator=(const comm_resp& from) {
    CopyFrom(from);
    return *this;
  }
  inline comm_resp& operator=(comm_resp&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const comm_resp& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const comm_resp* internal_default_instance() {
    return reinterpret_cast<const comm_resp*>(
               &_comm_resp_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(comm_resp* other);
  friend void swap(comm_resp& a, comm_resp& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline comm_resp* New() const final {
    return CreateMaybeMessage<comm_resp>(nullptr);
  }

  comm_resp* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<comm_resp>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const comm_resp& from);
  void MergeFrom(const comm_resp& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(comm_resp* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "common.comm_resp";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_comm_5fbasic_2eproto);
    return ::descriptor_table_comm_5fbasic_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string err_msg = 2;
  bool has_err_msg() const;
  void clear_err_msg();
  static const int kErrMsgFieldNumber = 2;
  const std::string& err_msg() const;
  void set_err_msg(const std::string& value);
  void set_err_msg(std::string&& value);
  void set_err_msg(const char* value);
  void set_err_msg(const char* value, size_t size);
  std::string* mutable_err_msg();
  std::string* release_err_msg();
  void set_allocated_err_msg(std::string* err_msg);

  // optional int32 err_code = 1;
  bool has_err_code() const;
  void clear_err_code();
  static const int kErrCodeFieldNumber = 1;
  ::PROTOBUF_NAMESPACE_ID::int32 err_code() const;
  void set_err_code(::PROTOBUF_NAMESPACE_ID::int32 value);

  // @@protoc_insertion_point(class_scope:common.comm_resp)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr err_msg_;
  ::PROTOBUF_NAMESPACE_ID::int32 err_code_;
  friend struct ::TableStruct_comm_5fbasic_2eproto;
};
// -------------------------------------------------------------------

class comm_request :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:common.comm_request) */ {
 public:
  comm_request();
  virtual ~comm_request();

  comm_request(const comm_request& from);
  comm_request(comm_request&& from) noexcept
    : comm_request() {
    *this = ::std::move(from);
  }

  inline comm_request& operator=(const comm_request& from) {
    CopyFrom(from);
    return *this;
  }
  inline comm_request& operator=(comm_request&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const comm_request& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const comm_request* internal_default_instance() {
    return reinterpret_cast<const comm_request*>(
               &_comm_request_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(comm_request* other);
  friend void swap(comm_request& a, comm_request& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline comm_request* New() const final {
    return CreateMaybeMessage<comm_request>(nullptr);
  }

  comm_request* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<comm_request>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const comm_request& from);
  void MergeFrom(const comm_request& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(comm_request* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "common.comm_request";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_comm_5fbasic_2eproto);
    return ::descriptor_table_comm_5fbasic_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string body = 2;
  bool has_body() const;
  void clear_body();
  static const int kBodyFieldNumber = 2;
  const std::string& body() const;
  void set_body(const std::string& value);
  void set_body(std::string&& value);
  void set_body(const char* value);
  void set_body(const char* value, size_t size);
  std::string* mutable_body();
  std::string* release_body();
  void set_allocated_body(std::string* body);

  // optional .common.comm_req head = 1;
  bool has_head() const;
  void clear_head();
  static const int kHeadFieldNumber = 1;
  const ::common::comm_req& head() const;
  ::common::comm_req* release_head();
  ::common::comm_req* mutable_head();
  void set_allocated_head(::common::comm_req* head);

  // @@protoc_insertion_point(class_scope:common.comm_request)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr body_;
  ::common::comm_req* head_;
  friend struct ::TableStruct_comm_5fbasic_2eproto;
};
// -------------------------------------------------------------------

class comm_response :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:common.comm_response) */ {
 public:
  comm_response();
  virtual ~comm_response();

  comm_response(const comm_response& from);
  comm_response(comm_response&& from) noexcept
    : comm_response() {
    *this = ::std::move(from);
  }

  inline comm_response& operator=(const comm_response& from) {
    CopyFrom(from);
    return *this;
  }
  inline comm_response& operator=(comm_response&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const comm_response& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const comm_response* internal_default_instance() {
    return reinterpret_cast<const comm_response*>(
               &_comm_response_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(comm_response* other);
  friend void swap(comm_response& a, comm_response& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline comm_response* New() const final {
    return CreateMaybeMessage<comm_response>(nullptr);
  }

  comm_response* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<comm_response>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const comm_response& from);
  void MergeFrom(const comm_response& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(comm_response* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "common.comm_response";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_comm_5fbasic_2eproto);
    return ::descriptor_table_comm_5fbasic_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string body = 2;
  bool has_body() const;
  void clear_body();
  static const int kBodyFieldNumber = 2;
  const std::string& body() const;
  void set_body(const std::string& value);
  void set_body(std::string&& value);
  void set_body(const char* value);
  void set_body(const char* value, size_t size);
  std::string* mutable_body();
  std::string* release_body();
  void set_allocated_body(std::string* body);

  // optional .common.comm_resp head = 1;
  bool has_head() const;
  void clear_head();
  static const int kHeadFieldNumber = 1;
  const ::common::comm_resp& head() const;
  ::common::comm_resp* release_head();
  ::common::comm_resp* mutable_head();
  void set_allocated_head(::common::comm_resp* head);

  // @@protoc_insertion_point(class_scope:common.comm_response)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr body_;
  ::common::comm_resp* head_;
  friend struct ::TableStruct_comm_5fbasic_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// comm_req

// optional int32 ver = 1;
inline bool comm_req::has_ver() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void comm_req::clear_ver() {
  ver_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 comm_req::ver() const {
  // @@protoc_insertion_point(field_get:common.comm_req.ver)
  return ver_;
}
inline void comm_req::set_ver(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000001u;
  ver_ = value;
  // @@protoc_insertion_point(field_set:common.comm_req.ver)
}

// optional int32 cmd = 2;
inline bool comm_req::has_cmd() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void comm_req::clear_cmd() {
  cmd_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 comm_req::cmd() const {
  // @@protoc_insertion_point(field_get:common.comm_req.cmd)
  return cmd_;
}
inline void comm_req::set_cmd(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  cmd_ = value;
  // @@protoc_insertion_point(field_set:common.comm_req.cmd)
}

// optional int32 sub_cmd = 3;
inline bool comm_req::has_sub_cmd() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void comm_req::clear_sub_cmd() {
  sub_cmd_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 comm_req::sub_cmd() const {
  // @@protoc_insertion_point(field_get:common.comm_req.sub_cmd)
  return sub_cmd_;
}
inline void comm_req::set_sub_cmd(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000004u;
  sub_cmd_ = value;
  // @@protoc_insertion_point(field_set:common.comm_req.sub_cmd)
}

// -------------------------------------------------------------------

// comm_resp

// optional int32 err_code = 1;
inline bool comm_resp::has_err_code() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void comm_resp::clear_err_code() {
  err_code_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 comm_resp::err_code() const {
  // @@protoc_insertion_point(field_get:common.comm_resp.err_code)
  return err_code_;
}
inline void comm_resp::set_err_code(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  err_code_ = value;
  // @@protoc_insertion_point(field_set:common.comm_resp.err_code)
}

// optional string err_msg = 2;
inline bool comm_resp::has_err_msg() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void comm_resp::clear_err_msg() {
  err_msg_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& comm_resp::err_msg() const {
  // @@protoc_insertion_point(field_get:common.comm_resp.err_msg)
  return err_msg_.GetNoArena();
}
inline void comm_resp::set_err_msg(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  err_msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:common.comm_resp.err_msg)
}
inline void comm_resp::set_err_msg(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  err_msg_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:common.comm_resp.err_msg)
}
inline void comm_resp::set_err_msg(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  err_msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:common.comm_resp.err_msg)
}
inline void comm_resp::set_err_msg(const char* value, size_t size) {
  _has_bits_[0] |= 0x00000001u;
  err_msg_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:common.comm_resp.err_msg)
}
inline std::string* comm_resp::mutable_err_msg() {
  _has_bits_[0] |= 0x00000001u;
  // @@protoc_insertion_point(field_mutable:common.comm_resp.err_msg)
  return err_msg_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* comm_resp::release_err_msg() {
  // @@protoc_insertion_point(field_release:common.comm_resp.err_msg)
  if (!has_err_msg()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return err_msg_.ReleaseNonDefaultNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void comm_resp::set_allocated_err_msg(std::string* err_msg) {
  if (err_msg != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  err_msg_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), err_msg);
  // @@protoc_insertion_point(field_set_allocated:common.comm_resp.err_msg)
}

// -------------------------------------------------------------------

// comm_request

// optional .common.comm_req head = 1;
inline bool comm_request::has_head() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void comm_request::clear_head() {
  if (head_ != nullptr) head_->Clear();
  _has_bits_[0] &= ~0x00000002u;
}
inline const ::common::comm_req& comm_request::head() const {
  const ::common::comm_req* p = head_;
  // @@protoc_insertion_point(field_get:common.comm_request.head)
  return p != nullptr ? *p : *reinterpret_cast<const ::common::comm_req*>(
      &::common::_comm_req_default_instance_);
}
inline ::common::comm_req* comm_request::release_head() {
  // @@protoc_insertion_point(field_release:common.comm_request.head)
  _has_bits_[0] &= ~0x00000002u;
  ::common::comm_req* temp = head_;
  head_ = nullptr;
  return temp;
}
inline ::common::comm_req* comm_request::mutable_head() {
  _has_bits_[0] |= 0x00000002u;
  if (head_ == nullptr) {
    auto* p = CreateMaybeMessage<::common::comm_req>(GetArenaNoVirtual());
    head_ = p;
  }
  // @@protoc_insertion_point(field_mutable:common.comm_request.head)
  return head_;
}
inline void comm_request::set_allocated_head(::common::comm_req* head) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete head_;
  }
  if (head) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      head = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, head, submessage_arena);
    }
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  head_ = head;
  // @@protoc_insertion_point(field_set_allocated:common.comm_request.head)
}

// optional string body = 2;
inline bool comm_request::has_body() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void comm_request::clear_body() {
  body_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& comm_request::body() const {
  // @@protoc_insertion_point(field_get:common.comm_request.body)
  return body_.GetNoArena();
}
inline void comm_request::set_body(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  body_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:common.comm_request.body)
}
inline void comm_request::set_body(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  body_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:common.comm_request.body)
}
inline void comm_request::set_body(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  body_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:common.comm_request.body)
}
inline void comm_request::set_body(const char* value, size_t size) {
  _has_bits_[0] |= 0x00000001u;
  body_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:common.comm_request.body)
}
inline std::string* comm_request::mutable_body() {
  _has_bits_[0] |= 0x00000001u;
  // @@protoc_insertion_point(field_mutable:common.comm_request.body)
  return body_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* comm_request::release_body() {
  // @@protoc_insertion_point(field_release:common.comm_request.body)
  if (!has_body()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return body_.ReleaseNonDefaultNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void comm_request::set_allocated_body(std::string* body) {
  if (body != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  body_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), body);
  // @@protoc_insertion_point(field_set_allocated:common.comm_request.body)
}

// -------------------------------------------------------------------

// comm_response

// optional .common.comm_resp head = 1;
inline bool comm_response::has_head() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void comm_response::clear_head() {
  if (head_ != nullptr) head_->Clear();
  _has_bits_[0] &= ~0x00000002u;
}
inline const ::common::comm_resp& comm_response::head() const {
  const ::common::comm_resp* p = head_;
  // @@protoc_insertion_point(field_get:common.comm_response.head)
  return p != nullptr ? *p : *reinterpret_cast<const ::common::comm_resp*>(
      &::common::_comm_resp_default_instance_);
}
inline ::common::comm_resp* comm_response::release_head() {
  // @@protoc_insertion_point(field_release:common.comm_response.head)
  _has_bits_[0] &= ~0x00000002u;
  ::common::comm_resp* temp = head_;
  head_ = nullptr;
  return temp;
}
inline ::common::comm_resp* comm_response::mutable_head() {
  _has_bits_[0] |= 0x00000002u;
  if (head_ == nullptr) {
    auto* p = CreateMaybeMessage<::common::comm_resp>(GetArenaNoVirtual());
    head_ = p;
  }
  // @@protoc_insertion_point(field_mutable:common.comm_response.head)
  return head_;
}
inline void comm_response::set_allocated_head(::common::comm_resp* head) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete head_;
  }
  if (head) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      head = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, head, submessage_arena);
    }
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  head_ = head;
  // @@protoc_insertion_point(field_set_allocated:common.comm_response.head)
}

// optional string body = 2;
inline bool comm_response::has_body() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void comm_response::clear_body() {
  body_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& comm_response::body() const {
  // @@protoc_insertion_point(field_get:common.comm_response.body)
  return body_.GetNoArena();
}
inline void comm_response::set_body(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  body_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:common.comm_response.body)
}
inline void comm_response::set_body(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  body_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:common.comm_response.body)
}
inline void comm_response::set_body(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  body_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:common.comm_response.body)
}
inline void comm_response::set_body(const char* value, size_t size) {
  _has_bits_[0] |= 0x00000001u;
  body_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:common.comm_response.body)
}
inline std::string* comm_response::mutable_body() {
  _has_bits_[0] |= 0x00000001u;
  // @@protoc_insertion_point(field_mutable:common.comm_response.body)
  return body_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* comm_response::release_body() {
  // @@protoc_insertion_point(field_release:common.comm_response.body)
  if (!has_body()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return body_.ReleaseNonDefaultNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void comm_response::set_allocated_body(std::string* body) {
  if (body != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  body_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), body);
  // @@protoc_insertion_point(field_set_allocated:common.comm_response.body)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace common

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_comm_5fbasic_2eproto