#include "frontend.hpp"
#include <cstdio>
#include <cstring>
#include <exception>

namespace simple_chat {

#define CHECK_RETURN_CODE   \
  if (return_code_ != -1) { \
    return return_code_;    \
  }

int ClientFrontend::Start(int argc, char** argv) {
  try {
    RunHelloStage(argc, argv);
    CHECK_RETURN_CODE
  } catch (const std::exception& e) {
    fprintf(stderr,
        "Exception occurred. Explanation is below.\n"
        "%s\n"
        "Program will exit now",
        e.what());
    return 1;
  }

  return 0;
}

void ClientFrontend::RunHelloStage(int argc, char** argv) {
  printf("Client for simple chat\n");

  if (argc == 1 || argc > 3 || (argc == 2 && strcmp(argv[1], "-h") == 0)) {
    printf("Usage: \n"
           "%s <port>\n"
           "%s <host> <port>\n",
           argv[0], argv[0]);
    return_code_ = 0;
    return;
  }

  const char* host = "127.0.0.1";
  const char* port = nullptr;
  if (argc == 2) {
    port = argv[1];
  } else {
    host = argv[1];
    port = argv[2];
  }

  backend_.Connect(host, port);
}

}  // namespace simple_chat