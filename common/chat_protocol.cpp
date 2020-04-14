#include <chat_protocol.hpp>

namespace simple_chat {

MessageLogin* MessageLogin::Create() {
  auto* obj = new MessageLogin;
  obj->header_.type_ = static_cast<uint32_t>(MessageType::LOGIN);
  obj->header_.body_size_ = sizeof(MessageLogin);
  return obj;
}

}  // namespace simple_chat
