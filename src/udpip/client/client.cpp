#include "client.h"

#include <iostream>

namespace s21 {
namespace udp {
namespace ip {
Client::Client(std::string name, unsigned short port)
    : name_(name), sock_(Socket::CreateSocket()), host_port_(port) {
  sock_->Bind();
}

void Client::Ping(std::chrono::seconds period) {
  while (true) {
    sock_->Send(host_port_, name_.c_str(), name_.length(), "127.0.0.1");
    std::this_thread::sleep_for(period);
  }
}
}  // namespace ip
}  // namespace udp
}  // namespace s21