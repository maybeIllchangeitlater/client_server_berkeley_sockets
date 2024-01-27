#include <iostream>

#include "client.h"

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cout
        << "Please specify client's name, port to connect to and ping delay"
        << std::endl;
  }
  std::string client_name(argv[1]);
  unsigned short host_port(std::stoi(argv[2]));
  std::chrono::seconds delay(std::stoi(argv[3]));
  s21::tcp::ip::Client cl(client_name);
  cl.Connect(host_port);
  cl.PingServerPeriodically(delay);
  return 0;
}