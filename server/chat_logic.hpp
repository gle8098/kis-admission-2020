#ifndef SIMPLE_CHAT_CHAT_LOGIC_HPP
#define SIMPLE_CHAT_CHAT_LOGIC_HPP

#include <vector>
#include <memory>
#include <chat_protocol.hpp>

namespace simple_chat {

class ClientSession;

class Chat {
public:
  int Join(ClientSession* session);

  template <typename T>
  void Broadcast(std::shared_ptr<T> msg);
private:
  std::vector<MessageHeader*> history_;
  std::vector<ClientSession*> companions_;
};

}  // namespace simple_chat

#endif // SIMPLE_CHAT_CHAT_LOGIC_HPP
