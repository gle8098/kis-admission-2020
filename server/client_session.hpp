#ifndef SIMPLE_CHAT_CLIENTSESSION_HPP
#define SIMPLE_CHAT_CLIENTSESSION_HPP

#include <vector>
#include <memory>
#include <chat_protocol.hpp>
#include <asio.hpp>
#include "chat_logic.hpp"

namespace simple_chat {

using asio::ip::tcp;

class ClientSession : public std::enable_shared_from_this<ClientSession> {
public:
  ClientSession(asio::io_service& io_service, Chat* chat);

  tcp::socket& GetSocket();

  void Start();

  template<typename T>
  void WriteMessage(std::shared_ptr<T> msg);

private:
  void RegReadListener();

  void ReadMsgListener(const asio::error_code& error, size_t bytes_transferred);

private:
  int id_ = -1;
  tcp::socket socket_;
  Chat* chat_;
  std::shared_ptr<AnyMessage> read_msg_mem_;
  MessageHeader* read_msg_;
};

}  // namespace simple_chat

#endif // SIMPLE_CHAT_CLIENTSESSION_HPP
