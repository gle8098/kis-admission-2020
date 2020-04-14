#include <chat_protocol.hpp>

namespace simple_chat {

MessageLogin::MessageLogin() {
  header_.type_ = static_cast<uint32_t>(MessageType::LOGIN);
  header_.body_size_ = sizeof(MessageLogin) - sizeof(MessageHeader);
}

}  // namespace simple_chat
