#ifndef CLIENT_FRONTEND_HPP
#define CLIENT_FRONTEND_HPP

#include "backend.hpp"
namespace simple_chat {

class ClientFrontend {
private:
  void RunHelloStage(int argc, char** argv);


public:
  int Start(int argc, char** argv);

private:
  int return_code_ = -1;
  ChatBackend backend_;
};

}  // namespace simple_chat

#endif // CLIENT_FRONTEND_HPP
