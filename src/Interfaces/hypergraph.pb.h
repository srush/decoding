// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hypergraph.proto

#ifndef PROTOBUF_hypergraph_2eproto__INCLUDED
#define PROTOBUF_hypergraph_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_hypergraph_2eproto();
void protobuf_AssignDesc_hypergraph_2eproto();
void protobuf_ShutdownFile_hypergraph_2eproto();

class Hypergraph;
class Hypergraph_Node;
class Hypergraph_Edge;

// ===================================================================

class Hypergraph_Node : public ::google::protobuf::Message {
 public:
  Hypergraph_Node();
  virtual ~Hypergraph_Node();
  
  Hypergraph_Node(const Hypergraph_Node& from);
  
  inline Hypergraph_Node& operator=(const Hypergraph_Node& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Hypergraph_Node& default_instance();
  
  void Swap(Hypergraph_Node* other);
  
  // implements Message ----------------------------------------------
  
  Hypergraph_Node* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Hypergraph_Node& from);
  void MergeFrom(const Hypergraph_Node& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);
  
  // optional string label = 2;
  inline bool has_label() const;
  inline void clear_label();
  static const int kLabelFieldNumber = 2;
  inline const ::std::string& label() const;
  inline void set_label(const ::std::string& value);
  inline void set_label(const char* value);
  inline void set_label(const char* value, size_t size);
  inline ::std::string* mutable_label();
  inline ::std::string* release_label();
  
  // repeated .Hypergraph.Edge edge = 3;
  inline int edge_size() const;
  inline void clear_edge();
  static const int kEdgeFieldNumber = 3;
  inline const ::Hypergraph_Edge& edge(int index) const;
  inline ::Hypergraph_Edge* mutable_edge(int index);
  inline ::Hypergraph_Edge* add_edge();
  inline const ::google::protobuf::RepeatedPtrField< ::Hypergraph_Edge >&
      edge() const;
  inline ::google::protobuf::RepeatedPtrField< ::Hypergraph_Edge >*
      mutable_edge();
  
  GOOGLE_PROTOBUF_EXTENSION_ACCESSORS(Hypergraph_Node)
  // @@protoc_insertion_point(class_scope:Hypergraph.Node)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_label();
  inline void clear_has_label();
  
  ::google::protobuf::internal::ExtensionSet _extensions_;
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* label_;
  ::google::protobuf::RepeatedPtrField< ::Hypergraph_Edge > edge_;
  ::google::protobuf::int32 id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_hypergraph_2eproto();
  friend void protobuf_AssignDesc_hypergraph_2eproto();
  friend void protobuf_ShutdownFile_hypergraph_2eproto();
  
  void InitAsDefaultInstance();
  static Hypergraph_Node* default_instance_;
};
// -------------------------------------------------------------------

class Hypergraph_Edge : public ::google::protobuf::Message {
 public:
  Hypergraph_Edge();
  virtual ~Hypergraph_Edge();
  
  Hypergraph_Edge(const Hypergraph_Edge& from);
  
  inline Hypergraph_Edge& operator=(const Hypergraph_Edge& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Hypergraph_Edge& default_instance();
  
  void Swap(Hypergraph_Edge* other);
  
  // implements Message ----------------------------------------------
  
  Hypergraph_Edge* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Hypergraph_Edge& from);
  void MergeFrom(const Hypergraph_Edge& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);
  
  // optional string label = 2;
  inline bool has_label() const;
  inline void clear_label();
  static const int kLabelFieldNumber = 2;
  inline const ::std::string& label() const;
  inline void set_label(const ::std::string& value);
  inline void set_label(const char* value);
  inline void set_label(const char* value, size_t size);
  inline ::std::string* mutable_label();
  inline ::std::string* release_label();
  
  // repeated int32 tail_node_ids = 3;
  inline int tail_node_ids_size() const;
  inline void clear_tail_node_ids();
  static const int kTailNodeIdsFieldNumber = 3;
  inline ::google::protobuf::int32 tail_node_ids(int index) const;
  inline void set_tail_node_ids(int index, ::google::protobuf::int32 value);
  inline void add_tail_node_ids(::google::protobuf::int32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      tail_node_ids() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_tail_node_ids();
  
  GOOGLE_PROTOBUF_EXTENSION_ACCESSORS(Hypergraph_Edge)
  // @@protoc_insertion_point(class_scope:Hypergraph.Edge)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_label();
  inline void clear_has_label();
  
  ::google::protobuf::internal::ExtensionSet _extensions_;
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* label_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > tail_node_ids_;
  ::google::protobuf::int32 id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_hypergraph_2eproto();
  friend void protobuf_AssignDesc_hypergraph_2eproto();
  friend void protobuf_ShutdownFile_hypergraph_2eproto();
  
  void InitAsDefaultInstance();
  static Hypergraph_Edge* default_instance_;
};
// -------------------------------------------------------------------

class Hypergraph : public ::google::protobuf::Message {
 public:
  Hypergraph();
  virtual ~Hypergraph();
  
  Hypergraph(const Hypergraph& from);
  
  inline Hypergraph& operator=(const Hypergraph& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Hypergraph& default_instance();
  
  void Swap(Hypergraph* other);
  
  // implements Message ----------------------------------------------
  
  Hypergraph* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Hypergraph& from);
  void MergeFrom(const Hypergraph& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef Hypergraph_Node Node;
  typedef Hypergraph_Edge Edge;
  
  // accessors -------------------------------------------------------
  
  // required int32 root = 5;
  inline bool has_root() const;
  inline void clear_root();
  static const int kRootFieldNumber = 5;
  inline ::google::protobuf::int32 root() const;
  inline void set_root(::google::protobuf::int32 value);
  
  // repeated .Hypergraph.Node node = 6;
  inline int node_size() const;
  inline void clear_node();
  static const int kNodeFieldNumber = 6;
  inline const ::Hypergraph_Node& node(int index) const;
  inline ::Hypergraph_Node* mutable_node(int index);
  inline ::Hypergraph_Node* add_node();
  inline const ::google::protobuf::RepeatedPtrField< ::Hypergraph_Node >&
      node() const;
  inline ::google::protobuf::RepeatedPtrField< ::Hypergraph_Node >*
      mutable_node();
  
  GOOGLE_PROTOBUF_EXTENSION_ACCESSORS(Hypergraph)
  // @@protoc_insertion_point(class_scope:Hypergraph)
 private:
  inline void set_has_root();
  inline void clear_has_root();
  
  ::google::protobuf::internal::ExtensionSet _extensions_;
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::Hypergraph_Node > node_;
  ::google::protobuf::int32 root_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_hypergraph_2eproto();
  friend void protobuf_AssignDesc_hypergraph_2eproto();
  friend void protobuf_ShutdownFile_hypergraph_2eproto();
  
  void InitAsDefaultInstance();
  static Hypergraph* default_instance_;
};
// ===================================================================


// ===================================================================

// Hypergraph_Node

// required int32 id = 1;
inline bool Hypergraph_Node::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Hypergraph_Node::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Hypergraph_Node::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Hypergraph_Node::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 Hypergraph_Node::id() const {
  return id_;
}
inline void Hypergraph_Node::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// optional string label = 2;
inline bool Hypergraph_Node::has_label() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Hypergraph_Node::set_has_label() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Hypergraph_Node::clear_has_label() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Hypergraph_Node::clear_label() {
  if (label_ != &::google::protobuf::internal::kEmptyString) {
    label_->clear();
  }
  clear_has_label();
}
inline const ::std::string& Hypergraph_Node::label() const {
  return *label_;
}
inline void Hypergraph_Node::set_label(const ::std::string& value) {
  set_has_label();
  if (label_ == &::google::protobuf::internal::kEmptyString) {
    label_ = new ::std::string;
  }
  label_->assign(value);
}
inline void Hypergraph_Node::set_label(const char* value) {
  set_has_label();
  if (label_ == &::google::protobuf::internal::kEmptyString) {
    label_ = new ::std::string;
  }
  label_->assign(value);
}
inline void Hypergraph_Node::set_label(const char* value, size_t size) {
  set_has_label();
  if (label_ == &::google::protobuf::internal::kEmptyString) {
    label_ = new ::std::string;
  }
  label_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Hypergraph_Node::mutable_label() {
  set_has_label();
  if (label_ == &::google::protobuf::internal::kEmptyString) {
    label_ = new ::std::string;
  }
  return label_;
}
inline ::std::string* Hypergraph_Node::release_label() {
  clear_has_label();
  if (label_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = label_;
    label_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// repeated .Hypergraph.Edge edge = 3;
inline int Hypergraph_Node::edge_size() const {
  return edge_.size();
}
inline void Hypergraph_Node::clear_edge() {
  edge_.Clear();
}
inline const ::Hypergraph_Edge& Hypergraph_Node::edge(int index) const {
  return edge_.Get(index);
}
inline ::Hypergraph_Edge* Hypergraph_Node::mutable_edge(int index) {
  return edge_.Mutable(index);
}
inline ::Hypergraph_Edge* Hypergraph_Node::add_edge() {
  return edge_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Hypergraph_Edge >&
Hypergraph_Node::edge() const {
  return edge_;
}
inline ::google::protobuf::RepeatedPtrField< ::Hypergraph_Edge >*
Hypergraph_Node::mutable_edge() {
  return &edge_;
}

// -------------------------------------------------------------------

// Hypergraph_Edge

// optional int32 id = 1;
inline bool Hypergraph_Edge::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Hypergraph_Edge::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Hypergraph_Edge::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Hypergraph_Edge::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 Hypergraph_Edge::id() const {
  return id_;
}
inline void Hypergraph_Edge::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// optional string label = 2;
inline bool Hypergraph_Edge::has_label() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Hypergraph_Edge::set_has_label() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Hypergraph_Edge::clear_has_label() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Hypergraph_Edge::clear_label() {
  if (label_ != &::google::protobuf::internal::kEmptyString) {
    label_->clear();
  }
  clear_has_label();
}
inline const ::std::string& Hypergraph_Edge::label() const {
  return *label_;
}
inline void Hypergraph_Edge::set_label(const ::std::string& value) {
  set_has_label();
  if (label_ == &::google::protobuf::internal::kEmptyString) {
    label_ = new ::std::string;
  }
  label_->assign(value);
}
inline void Hypergraph_Edge::set_label(const char* value) {
  set_has_label();
  if (label_ == &::google::protobuf::internal::kEmptyString) {
    label_ = new ::std::string;
  }
  label_->assign(value);
}
inline void Hypergraph_Edge::set_label(const char* value, size_t size) {
  set_has_label();
  if (label_ == &::google::protobuf::internal::kEmptyString) {
    label_ = new ::std::string;
  }
  label_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Hypergraph_Edge::mutable_label() {
  set_has_label();
  if (label_ == &::google::protobuf::internal::kEmptyString) {
    label_ = new ::std::string;
  }
  return label_;
}
inline ::std::string* Hypergraph_Edge::release_label() {
  clear_has_label();
  if (label_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = label_;
    label_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// repeated int32 tail_node_ids = 3;
inline int Hypergraph_Edge::tail_node_ids_size() const {
  return tail_node_ids_.size();
}
inline void Hypergraph_Edge::clear_tail_node_ids() {
  tail_node_ids_.Clear();
}
inline ::google::protobuf::int32 Hypergraph_Edge::tail_node_ids(int index) const {
  return tail_node_ids_.Get(index);
}
inline void Hypergraph_Edge::set_tail_node_ids(int index, ::google::protobuf::int32 value) {
  tail_node_ids_.Set(index, value);
}
inline void Hypergraph_Edge::add_tail_node_ids(::google::protobuf::int32 value) {
  tail_node_ids_.Add(value);
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
Hypergraph_Edge::tail_node_ids() const {
  return tail_node_ids_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
Hypergraph_Edge::mutable_tail_node_ids() {
  return &tail_node_ids_;
}

// -------------------------------------------------------------------

// Hypergraph

// required int32 root = 5;
inline bool Hypergraph::has_root() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Hypergraph::set_has_root() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Hypergraph::clear_has_root() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Hypergraph::clear_root() {
  root_ = 0;
  clear_has_root();
}
inline ::google::protobuf::int32 Hypergraph::root() const {
  return root_;
}
inline void Hypergraph::set_root(::google::protobuf::int32 value) {
  set_has_root();
  root_ = value;
}

// repeated .Hypergraph.Node node = 6;
inline int Hypergraph::node_size() const {
  return node_.size();
}
inline void Hypergraph::clear_node() {
  node_.Clear();
}
inline const ::Hypergraph_Node& Hypergraph::node(int index) const {
  return node_.Get(index);
}
inline ::Hypergraph_Node* Hypergraph::mutable_node(int index) {
  return node_.Mutable(index);
}
inline ::Hypergraph_Node* Hypergraph::add_node() {
  return node_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Hypergraph_Node >&
Hypergraph::node() const {
  return node_;
}
inline ::google::protobuf::RepeatedPtrField< ::Hypergraph_Node >*
Hypergraph::mutable_node() {
  return &node_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_hypergraph_2eproto__INCLUDED
