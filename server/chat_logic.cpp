#include "chat_logic.hpp"
#include "client_session.hpp"

namespace simple_chat {

int simple_chat::Chat::Join(simple_chat::ClientSession *session) {
  if (companions_.size() >= MAX_COMPANIONS) {
    return -1;
  }
  companions_.push_back(session);
  return companions_.size() - 1;
}

template <typename T>
void Chat::Broadcast(std::shared_ptr<T> msg) {
  for (ClientSession* session : companions_) {
    session->WriteMessage(msg);
  }
}

}  // namespace simple_chat