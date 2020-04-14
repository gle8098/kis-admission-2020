#include "client_session.hpp"

namespace simple_chat {

ClientSession::ClientSession(asio::io_service &io_service, Chat *chat)
        : socket_(io_service), chat_(chat), read_msg_(nullptr) {
  read_msg_mem_ = std::make_shared<AnyMessage>();
  read_msg_ = reinterpret_cast<MessageHeader *>(read_msg_mem_.get());
}

tcp::socket &ClientSession::GetSocket() {
  return socket_;
}

void ClientSession::Start() {
  id_ = chat_->Join(this);
  RegReadListener();
}

template <typename T>
void ClientSession::WriteMessage(std::shared_ptr<T> msg) {
  asio::async_write(socket_, asio::buffer(msg, sizeof(T)),
                    [msg](const asio::error_code& error, size_t bytes_sent) {
                      (void)(msg);
                    }
  );
}

void ClientSession::RegReadListener() {
  asio::async_read(socket_, asio::buffer(read_msg_, MAX_MSG_LEN),
                   [this](const asio::error_code& error, size_t bytes_transferred) {
                     ReadMsgListener(error, bytes_transferred);
                   });
}

void ClientSession::ReadMsgListener(const asio::error_code &error,
                                    size_t bytes_transferred) {
  if (!error) {
    printf("Recv msg body %d type %d\n", read_msg_->body_size_,
           read_msg_->type_);
  }
  RegReadListener();
}

}  // namespace simple_chat
