#include <iostream>

#include "client.h"

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cout
        << "please specify client name, server port and ping delay in seconds"
        << std::endl;
    exit(1);
  }
  s21::udp::ip::Client client(argv[1], std::stoi(argv[2]));
  client.Ping(std::chrono::seconds(std::atoi(argv[3])));
  return 0;
}