#include <asio.hpp>
#include <chat_protocol.hpp>
#include <deque>
#include <iostream>
#include <set>

namespace simple_chat {

using asio::ip::tcp;

class Chat;
class ClientSession;

class ClientSession : public std::enable_shared_from_this<ClientSession> {
public:
  ClientSession(asio::io_service& io_service, Chat* chat)
      : socket_(io_service), chat_(chat) {
  }

  tcp::socket& GetSocket() {
    return socket_;
  }

  void Start() {
    chat_.Login();
    RegReadListener();
  }

  template<typename T>
  void WriteMessage(T* msg) {
    asio::async_write(socket_, asio::buffer(msg, sizeof(T)),
        [msg](const asio::error_code& error, size_t bytes_sent) {
          delete msg;
        }
    );
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

  /*void start() {
    room_.join(shared_from_this());
    asio::async_read(
        socket_, asio::buffer(read_msg_.data(), chat_message::header_length),
        bind(&ClientSession::handle_read_header, shared_from_this(),
             asio::placeholders::error));
  }

  void deliver(const chat_message &msg) {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress) {
      asio::async_write(socket_,
                        asio::buffer(write_msgs_.front().data(),
                                     write_msgs_.front().length()),
                        bind(&ClientSession::handle_write, shared_from_this(),
                             asio::placeholders::error));
    }
  }

  void handle_read_header(const asio::error_code &error) {
    if (!error && read_msg_.decode_header()) {
      asio::async_read(socket_,
                       asio::buffer(read_msg_.body(), read_msg_.body_length()),
                       bind(&ClientSession::handle_read_body, shared_from_this(),
                            asio::placeholders::error));
    } else {
      room_.leave(shared_from_this());
    }
  }

  void handle_read_body(const asio::error_code &error) {
    if (!error) {
      room_.deliver(read_msg_);
      asio::async_read(
          socket_, asio::buffer(read_msg_.data(), chat_message::header_length),
          bind(&ClientSession::handle_read_header, shared_from_this(),
               asio::placeholders::error));
    } else {
      room_.leave(shared_from_this());
    }
  }

  void handle_write(const asio::error_code &error) {
    if (!error) {
      write_msgs_.pop_front();
      if (!write_msgs_.empty()) {
        asio::async_write(socket_,
                          asio::buffer(write_msgs_.front().data(),
                                       write_msgs_.front().length()),
                          bind(&ClientSession::handle_write, shared_from_this(),
                               asio::placeholders::error));
      }
    } else {
      room_.leave(shared_from_this());
    }
  }*/

private:
  tcp::socket socket_;
  Chat* chat_;
  MessageHeader* read_msg_;
};

typedef std::shared_ptr<ClientSession> chat_session_ptr;

class Chat {

private:
  std::vector<MessageHeader*> history_;
  std::vector<ClientSession> companions_;
};

class Server {
public:
  Server(asio::io_service &io_service, const tcp::endpoint &endpoint)
      : io_service_(io_service), acceptor_(io_service, endpoint) {
    StartAccept();
  }

  void StartAccept() {
    auto session = std::make_shared<ClientSession>(io_service_, &chat_);
    acceptor_.async_accept(session->GetSocket(),
                           [this, session](const asio::error_code& error) {
      if (!error) {
        session->Start();
      }
      StartAccept();
    });
  }

private:
  asio::io_service &io_service_;
  tcp::acceptor acceptor_;
  Chat chat_;
};

int main(int argc, char **argv) {
  try {
    if (argc < 2) {
      printf("Usage: %s <port>\n", argv[0]);
      return 0;
    }

    asio::io_service io_service;

    tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[1]));
    Server server(io_service, endpoint);

    io_service.run();
  } catch (std::exception &e) {
    printf("Exception: %s\n", e.what());
  }

  return 0;
}

}  // namespace simple_chat
