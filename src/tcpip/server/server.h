#ifndef CLIENT_SERVER_BERKELEY_SOCKETS_TCPIP_SERVER_SERVER_H
#define CLIENT_SERVER_BERKELEY_SOCKETS_TCPIP_SERVER_SERVER_H

#include <fstream>
#include <thread>

#include "../common/socket.h"
#include "../common/thread_safe_que.h"
#include "../common/timestamper.h"
#include "acceptor.h"

namespace s21 {
namespace tcp {
namespace ip {
class Server {
 public:
  explicit Server(unsigned short port);
  ~Server();

 private:
  void HandlePing(std::shared_ptr<Socket> connection);
  void LogFromQue();
  void InitializeAcceptThread();
  void InitializeLoggingThread();

 private:
  std::ofstream log_file_;
  s21::ThreadSafeQ<std::string> msg_que_;
  std::thread accept_thread_;
  std::thread write_to_log_thread_;
  Acceptor acceptor_;
};
}  // namespace ip
}  // namespace tcp
}  // namespace s21

#endif  // CLIENT_SERVER_BERKELEY_SOCKETS_TCPIP_SERVER_SERVER_H
