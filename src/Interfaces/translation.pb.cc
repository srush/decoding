// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "translation.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {


}  // namespace


void protobuf_AssignDesc_translation_2eproto() {
  protobuf_AddDesc_translation_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "translation.proto");
  GOOGLE_CHECK(file != NULL);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_translation_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_translation_2eproto() {
}

void protobuf_AddDesc_translation_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::protobuf_AddDesc_hypergraph_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021translation.proto\032\020hypergraph.proto:%\n"
    "\020foreign_sentence\022\013.Hypergraph\030\001 \001(\t:(\n\023"
    "reference_sentences\022\013.Hypergraph\030\002 \003(\t", 118);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "translation.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::Hypergraph::default_instance(),
    1, 9, false, false);
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::Hypergraph::default_instance(),
    2, 9, true, false);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_translation_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_translation_2eproto {
  StaticDescriptorInitializer_translation_2eproto() {
    protobuf_AddDesc_translation_2eproto();
  }
} static_descriptor_initializer_translation_2eproto_;

const ::std::string foreign_sentence_default("");
::google::protobuf::internal::ExtensionIdentifier< ::Hypergraph,
    ::google::protobuf::internal::StringTypeTraits, 9, false >
  foreign_sentence(kForeignSentenceFieldNumber, foreign_sentence_default);
const ::std::string reference_sentences_default("");
::google::protobuf::internal::ExtensionIdentifier< ::Hypergraph,
    ::google::protobuf::internal::RepeatedStringTypeTraits, 9, false >
  reference_sentences(kReferenceSentencesFieldNumber, reference_sentences_default);

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
