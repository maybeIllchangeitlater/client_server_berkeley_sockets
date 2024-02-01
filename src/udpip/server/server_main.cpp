#include "server.h"

int main(int argc, char *argv[]) {
  if ((argc) < 2) {
    std::cout << "please enter port to run server on" << std::endl;
    exit(1);
  }
  s21::udp::ip::Server server(std::stoi(argv[1]));
  std::cout << "server is running press q to exit" << std::endl;
  while (std::getchar() != 'q') {
  }
  return 0;
}