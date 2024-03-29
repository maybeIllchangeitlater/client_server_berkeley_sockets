#ifndef CLIENT_SERVER_BERKELEY_SOCKETS_UDPIP_CLIENT_CLIENT_H
#define CLIENT_SERVER_BERKELEY_SOCKETS_UDPIP_CLIENT_CLIENT_H

#include <chrono>
#include <string>
#include <thread>

#include "../common/socket.h"

namespace s21 {
namespace udp {
namespace ip {
class Client {
 public:
  Client(std::string name, unsigned short port);
  void Ping(std::chrono::seconds period);

 private:
  std::string name_;
  std::shared_ptr<Socket> sock_;
  unsigned short host_port_;
};
}  // namespace ip
}  // namespace udp
}  // namespace s21

#endif  // CLIENT_SERVER_BERKELEY_SOCKETS_UDPIP_CLIENT_CLIENT_H
