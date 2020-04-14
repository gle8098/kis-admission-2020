#ifndef SIMPLE_CHAT_CHAT_PROTOCOL_HPP
#define SIMPLE_CHAT_CHAT_PROTOCOL_HPP

#include <cstdint>

namespace simple_chat {

enum { MAX_MSG_LEN = 1024 };

enum struct MessageType : uint32_t {
  LOGIN, MESSAGE, GET_HISTORY
};

struct MessageHeader {
  uint32_t type_{};
  uint32_t body_size_{};
};

struct MessageLogin {
  MessageHeader header_;

  static MessageLogin* Create();
};

}  // namespace simple_chat

#endif // SIMPLE_CHAT_CHAT_PROTOCOL_HPP
