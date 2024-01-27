#include <iostream>

#include "server.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Please specify port to launch server on" << std::endl;
    exit(1);
  }
  unsigned short port = std::stoi(argv[1]);
  s21::tcp::ip::Server server(port);
  std::cout << "Server is running on port " << port << ", press q to exit"
            << std::endl;
  while (std::getchar() != 'q') {
  }
  return 0;
}

/// move acceptor things from header to cpp
/// thread safe for connections list