#include "client.h"

int main(int argc, char *argv[]) {
  s21::udp::ip::Client client(argv[1], 8080);
  client.Ping(std::chrono::seconds(std::atoi(argv[2])));
  return 0;
}