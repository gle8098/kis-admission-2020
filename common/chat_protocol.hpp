#ifndef SIMPLE_CHAT_CHAT_PROTOCOL_HPP
#define SIMPLE_CHAT_CHAT_PROTOCOL_HPP

#include <cstddef>
#include <cstdint>

namespace simple_chat {

enum { MAX_MSG_LEN = 1024, MAX_COMPANIONS = 5 };
typedef struct {
  char _[MAX_MSG_LEN];
} AnyMessage;

enum struct MessageType : uint32_t {
  LOGIN, MESSAGE, GET_HISTORY
};

struct MessageHeader {
  uint32_t type_{};
  uint32_t body_size_{};
};

struct MessageLogin {
  MessageHeader header_{};

  MessageLogin();
};

struct MessageWritten {
  MessageHeader header_;
  char written[512] = {};

  MessageWritten();
};

struct MessageGetHistory {
  MessageHeader header_;
  int requested_id{};  // если = -1, значит означает id себя

  MessageGetHistory();
};

}  // namespace simple_chat

#endif // SIMPLE_CHAT_CHAT_PROTOCOL_HPP
