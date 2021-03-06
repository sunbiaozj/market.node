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
#ifndef FILESENDER_H
#define FILESENDER_H
#include <Common/QuickFAST_Export.h>
#include "FileSender_fwd.h"
#include <Communication/Sender.h>
namespace QuickFAST
{
  namespace Communication
  {
    /// @brief Simple implementaton of the Sender interface.  Writes the data to a file.
    class FileSender: public Sender
    {
    public:
      /// @brief construct
      /// @param recycler to take care of empty buffers
      /// @param fileName is the name of the file to be written
      /// @param binary controls end-of-line handling on Windows.  Ignored on other platforms.
      FileSender(
        BufferRecycler & recycler,
        const char * fileName,
        bool binary = false);

      virtual ~FileSender();
      // Override Sender method
      virtual void open();
      // Override Sender method
      virtual void send(LinkedBuffer * buffer);
      // Override Sender method
      virtual void close();

    private:
      FileSender & operator=(FileSender &); // no autogenerated assignment
    private:
      std::string fileName_;
      bool binary_;
      FILE * file_;
    };
  }
}
#endif // FILESENDER_H
