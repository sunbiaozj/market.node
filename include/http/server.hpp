//
// server.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2013 (alex at furosys.com) 
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#pragma once

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "connection.hpp"
#include "io_service_pool.hpp"
#include "request_handler.hpp"

namespace http {
    namespace market {
        /// The top-level class of the HTTP server.
        class server : private boost::noncopyable {
            public:
                /// Construct the server to listen on the specified TCP address and port, and
                /// serve up files from the given directory.
                explicit server(
                    const std::string& address,
                    const std::string& port,
                    const std::string& doc_root,
                    std::size_t io_service_pool_size
                );
                /// Run the server's io_service loop.
                void run();
            private:
                /// Initiate an asynchronous accept operation.
                void start_accept();
                /// Handle completion of an asynchronous accept operation.
                void handle_accept(const boost::system::error_code& e);
                /// Handle a request to stop the server.
                void handle_stop();
                /// The pool of io_service objects used to perform asynchronous operations.
                io_service_pool io_service_pool_;
                /// The signal_set is used to register for process termination notifications.
                boost::asio::signal_set signals_;
                /// Acceptor used to listen for incoming connections.
                boost::asio::ip::tcp::acceptor acceptor_;
                /// The next connection to be accepted.
                connection_ptr new_connection_;
                /// The handler for all incoming requests.
                request_handler request_handler_;
        };
    } // namespace market
} // namespace http
