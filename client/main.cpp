#include "frontend.hpp"

int main(int argc, char** argv) {
  simple_chat::ClientFrontend frontend;
  frontend.Start(argc, argv);
  return 0;
}
