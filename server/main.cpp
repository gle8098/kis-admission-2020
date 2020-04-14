#include "server.hpp"
#include <cstdio>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <port>\n", argv[0]);
    return 0;
  }

  try {
    auto server = simple_chat::Server::CreateServer(std::atoi(argv[1]));
    server->Run();
  } catch (std::exception &e) {
    printf("Exception: %s\n", e.what());
  }

  return 0;
}
