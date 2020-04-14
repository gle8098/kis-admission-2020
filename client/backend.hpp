#ifndef CLIENT_BACKEND_HPP
#define CLIENT_BACKEND_HPP

#include <asio/io_service.hpp>
#include <memory>

namespace simple_chat {

class ChatConnection;

class ChatBackend {
public:
  void Connect(const char *host, const char *port);

private:
  asio::io_service io_service;
  std::shared_ptr<ChatConnection> con_;
};

}  // namespace simple_chat

#endif // CLIENT_BACKEND_HPP
