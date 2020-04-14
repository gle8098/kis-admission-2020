#include "server.hpp"

namespace simple_chat {

Server::Server(const tcp::endpoint &endpoint)
    : acceptor_(io_service_, endpoint) {
  StartAccept();
}

void Server::StartAccept() {
  auto session = std::make_shared<ClientSession>(io_service_, &chat_);
  acceptor_.async_accept(session->GetSocket(),
                         [this, session](const asio::error_code& error) {
                           if (!error) {
                             session->Start();
                           }
                           StartAccept();
                         });
}



std::shared_ptr<Server> Server::CreateServer(int port) {
  tcp::endpoint endpoint(tcp::v4(), port);
  auto server = std::make_shared<Server>(endpoint);

  return server;
}

void Server::Run() {
  io_service_.run();
}

}  // namespace simple_chat