#include "client.h"

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cout
        << "please specify server port, client name and ping delay in seconds"
        << std::endl;
    exit(1);
  }
  s21::udp::ip::Client client(argv[1], argv[2]);
  client.Ping(std::chrono::seconds(std::atoi(argv[3])));
  return 0;
}