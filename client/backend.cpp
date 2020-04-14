#include "backend.hpp"
#include <asio.hpp>
#include <chat_protocol.hpp>
#include <deque>
#include <functional>

using asio::ip::tcp;

namespace simple_chat {

struct ChatConnection {
  enum struct Stage { HELLO, CHATTING, SHUTDOWN };

  explicit ChatConnection(asio::io_service& io_service)
   : stage_(Stage::HELLO), socket_(io_service), read_msg_(nullptr) {
    read_msg_ = reinterpret_cast<MessageHeader *>(new char[MAX_MSG_LEN]);

    RegReadListener();
    SendHelloMsg();
  }

  template<typename T>
  void WriteMessage(T* msg) {
      asio::async_write(socket_, asio::buffer(msg, sizeof(T)),
          [msg](const asio::error_code& error, size_t bytes_sent) {
            delete msg;
          }
      );
  }

  void SendHelloMsg() {
    WriteMessage(MessageLogin::Create());
  }

  void RegReadListener() {
    asio::async_read(socket_, asio::buffer(read_msg_, MAX_MSG_LEN),
        [this](const asio::error_code& error, size_t bytes_transferred) {
      ReadMsgListener(error, bytes_transferred);
    });
  }

  void ReadMsgListener(const asio::error_code& error, size_t bytes_transferred) {
    printf("Recv msg body %d type %d\n", read_msg_->body_size_, read_msg_->type_);
    RegReadListener();
  }

  Stage stage_;
  tcp::socket socket_;
  MessageHeader* read_msg_;
};

void ChatBackend::Connect(const char *host, const char *port) {
  tcp::resolver resolver(io_service);
  tcp::resolver::query query(host, port);
  tcp::resolver::iterator iterator = resolver.resolve(query);

  con_ = std::make_shared<ChatConnection>(io_service);
  asio::connect(con_->socket_, iterator);

  asio::thread t([this]() { io_service.run(); });
}

}
