// Copyright (c) 2009, 2010, 2011 Object Computing, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimer in the documentation
//      and/or other materials provided with the distribution.
//    * Neither the name of Object Computing, Inc. nor the names of its
//      contributors may be used to endorse or promote products derived from this
//      software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifdef _MSC_VER
# pragma once
#endif
#ifndef VALUEMESSAGEBUILDER_H
#define VALUEMESSAGEBUILDER_H
#include "ValueMessageBuilder_fwd.h"
#include <Common/QuickFAST_Export.h>
#include <Common/Types.h>
#include <Messages/FieldIdentity_fwd.h>
#include <Common/Logger.h>
namespace QuickFAST{
  namespace Messages{
    /// @brief Interface to support building a message during decoding.
    class ValueMessageBuilder : public Common::Logger
    {
    public:

      /// @brief Virtual destructor
      virtual ~ValueMessageBuilder(){}

      /// @brief get the application type associated with
      /// this set of fields via typeref.
      virtual const std::string & getApplicationType()const = 0;

      /// @brief get the namespace for the application type
      virtual const std::string & getApplicationTypeNs()const = 0;

      /// @brief Add a field to the set.
      ///
      /// @param identity identifies this field
      /// @param type is the type of data to be added
      /// @param value is the value to be assigned.
      virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const int64 value) = 0;
      /// @brief Add a field to the set.
      ///
      /// @param identity identifies this field
      /// @param type is the type of data to be added
      /// @param value is the value to be assigned.
      virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const uint64 value) = 0;
      /// @brief Add a field to the set.
      ///
      /// @param identity identifies this field
      /// @param type is the type of data to be added
      /// @param value is the value to be assigned.
      virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const int32 value) = 0;
      /// @brief Add a field to the set.
      ///
      /// @param identity identifies this field
      /// @param type is the type of data to be added
      /// @param value is the value to be assigned.
      virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const uint32 value) = 0;
      /// @brief Add a field to the set.
      ///
      /// @param identity identifies this field
      /// @param type is the type of data to be added
      /// @param value is the value to be assigned.
      virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const int16 value) = 0;
      /// @brief Add a field to the set.
      ///
      /// @param identity identifies this field
      /// @param type is the type of data to be added
      /// @param value is the value to be assigned.
      virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const uint16 value) = 0;
      /// @brief Add a field to the set.
      ///
      /// @param identity identifies this field
      /// @param type is the type of data to be added
      /// @param value is the value to be assigned.
      virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const int8 value) = 0;
      /// @brief Add a field to the set.
      ///
      /// @param identity identifies this field
      /// @param type is the type of data to be added
      /// @param value is the value to be assigned.
      virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const uchar value) = 0;
      /// @brief Add a field to the set.
      ///
      /// @param identity identifies this field
      /// @param type is the type of data to be added
      /// @param value is the value to be assigned.
      virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const Decimal& value) = 0;
      /// @brief Add a field to the set.
      ///
      /// @param identity identifies this field
      /// @param type is the type of data to be added
      /// @param value is the value to be assigned.
      /// @param length is the length of the string pointed to by value
      virtual void addValue(FieldIdentityCPtr & identity, ValueType::Type type, const unsigned char * value, size_t length) = 0;

      /// @brief prepare to accept an entire message
      ///
      /// @param applicationType is the data type for the message
      /// @param applicationTypeNamespace qualifies applicationTYpe
      /// @param size is the maximum number of fields to expect in the message
      /// @returns a message builder that will accept the fields in the message
      ///        (which may be *this)
      virtual ValueMessageBuilder & startMessage(
        const std::string & applicationType,
        const std::string & applicationTypeNamespace,
        size_t size) = 0;

      /// @brief Finish a message.  Process the result.
      ///
      /// @param messageBuilder is the builder provided by startMessage()
      /// @returns true if decoding should continue
      virtual bool endMessage(ValueMessageBuilder & messageBuilder) = 0;

      /// @brief Finish a message.  Ignore the result.
      ///
      /// @param messageBuilder is the builder provided by startMessage()
      /// @returns true if decoding should continue
      virtual bool ignoreMessage(ValueMessageBuilder & messageBuilder) = 0;

      /// @brief prepare to accept decoded sequence entries
      ///
      /// @param identity identifies the sequence
      /// @param applicationType is the data type for a sequence entry
      /// @param applicationTypeNamespace qualifies applicationTYpe
      /// @param fieldCount is the maximum number of fields to expect in each entry
      /// @param lengthIdentity is the identity of the length field
      /// @param length is a count of how many entries will be in the sequence
      virtual ValueMessageBuilder & startSequence(
        FieldIdentityCPtr & identity,
        const std::string & applicationType,
        const std::string & applicationTypeNamespace,
        size_t fieldCount,
        FieldIdentityCPtr & lengthIdentity,
        size_t length) = 0;

      /// @brief Complete the entire sequence.
      ///
      /// Builders may assume that all Sequence Entries will be closed via endSequenceEntry
      ///
      /// @param identity identifies the sequence
      /// @param sequenceBuilder is the builder provided by startSequence
      virtual void endSequence(
        FieldIdentityCPtr & identity,
        ValueMessageBuilder & sequenceBuilder) = 0;

      /// @brief prepare to accept a single decoded sequence entry
      ///
      /// Builders may assume this call is nested within a startSequence/endSequence pair.
      ///
      /// @param applicationType is the data type for the entry
      /// @param applicationTypeNamespace qualifies applicationTYpe
      /// @param size is the maximum number of fields to expect in the entry
      /// @returns a ValueMessageBuilder to accumulate fields for this entry (*this is ok).
      virtual ValueMessageBuilder & startSequenceEntry(
        const std::string & applicationType,
        const std::string & applicationTypeNamespace,
        size_t size)  = 0;

      /// @brief Complete the current sequence entry.
      ///
      /// This method is called on the <b>containing</b> ValueMessageBuilder
      ///
      /// Builders may assume this call follows a startSequenceEntry call within
      //  a startSequence/endSequence pair.
      ///
      /// @param entry the nested Message builder returned by startSequenceEntry.
      virtual void endSequenceEntry(ValueMessageBuilder & entry) = 0;

      /// @brief Prepare to accept a decoded Group
      /// @param identity identifies the group
      /// @param applicationType is the data type for the group
      /// @param applicationTypeNamespace qualifies applicationTYpe
      /// @param size is the maximum number of fields to expect in the group
      /// @returns a ValueMessageBuilder to accumulate fields for this group (*this is ok)
      virtual ValueMessageBuilder & startGroup(
        FieldIdentityCPtr & identity,
        const std::string & applicationType,
        const std::string & applicationTypeNamespace,
        size_t size) = 0;

      /// @brief Complete the group
      ///
      /// @param identity identifies the group
      /// @param groupBuilder is the message builder returned by startGroup
      virtual void endGroup(
        FieldIdentityCPtr & identity,
        ValueMessageBuilder & groupBuilder) = 0;

      /// @brief Notify builder that packets are missing
      ///
      /// Called when packet sequence numbers are being used for arbitrage.
      /// No action is required.  This is for information only.
      /// The method will be called after decoding the startGap-1th packet
      /// and before decoding the endGap'th packet.
      ///
      /// New method added to the interface.  It's not pure virtual to avoid
      /// breaking existing implementations.
      ///
      /// @param startGap the sequence number of the first missing packet
      /// @param endGap the sequence number of the first packet present after the gap.
      virtual void reportGap(sequence_t startGap, sequence_t endGap)
      {
      }

    };
  }
}
#endif // VALUEMESSAGEBUILDER_H
