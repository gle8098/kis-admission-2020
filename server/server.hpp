#ifndef SIMPLE_CHAT_SERVER_HPP
#define SIMPLE_CHAT_SERVER_HPP

#include <asio.hpp>
#include <memory>
#include "client_session.hpp"

namespace simple_chat {

using asio::ip::tcp;

class Server {
public:
  static std::shared_ptr<Server> CreateServer(int port);

  void Run();

  Server(const tcp::endpoint &endpoint);

private:
  void StartAccept();

private:
  asio::io_service io_service_;
  tcp::acceptor acceptor_;
  Chat chat_;
};

}  // namespace simple_chat

#endif // SIMPLE_CHAT_SERVER_HPP
