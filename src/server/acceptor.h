#ifndef CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_ACCEPTOR_H_
#define CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_ACCEPTOR_H_

#include <future>

#include "../common/socket.h"

namespace s21 {
namespace tcp {
namespace ip {
/// Acceptor socket for server. Responsible for accepting connections
class Acceptor : protected Socket {
 public:
  constexpr static const short BACKLOG_LIMIT = 128;
  /// creates Acceptor sockets and binds it to port
  /// Acceptor immediately starts listening on specified port
  explicit Acceptor(unsigned short port);
  /// Asynchronously accepts connections
  std::future<std::shared_ptr<Socket>> AsyncAccept();
  /// Accepts connection and returns shared ptr to socket object for it
  std::shared_ptr<Socket> Accept();
};
}  // namespace ip
}  // namespace tcp
}  // namespace s21

#endif  // CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_ACCEPTOR_H_