#ifndef CLIENT_SERVER_BERKELEY_SOCKETS_UDPIP_COMMON_SOCKET_H
#define CLIENT_SERVER_BERKELEY_SOCKETS_UDPIP_COMMON_SOCKET_H

#include <arpa/inet.h>   //inet_pton (converts addresses from text to binary)
#include <netinet/in.h>  //for sockaddr_in
#include <sys/socket.h>
#include <unistd.h>  //for close()

#include <cstring>  //for memset
#include <memory>
#include <stdexcept>

namespace s21 {
namespace udp {
namespace ip {
/// non-copyable, non-movable object representing BSD/UNIX internet socket
/// for UDP/IPv4 connection
/// Accessed from outside by shared_ptr
class Socket {
 public:
  Socket(const Socket &other) = delete;
  Socket(Socket &&other) = delete;
  Socket &operator=(const Socket &other) = delete;
  Socket &operator=(Socket &&other) = delete;
  ~Socket();
  /// Creates shared ptr on socket for UDP/IP connection
  static std::shared_ptr<Socket> CreateSocket() {
    struct MakeSharedEnabler : public Socket {};
    return std::make_shared<MakeSharedEnabler>();
  }
  /// binds sockets to address and port
  void Bind(unsigned short port = 0, const char *address = "127.0.0.1");
  /// Reads into buffer of max length buffer_length. Returns amount of bytes
  /// read
  size_t Receive(char *buffer, size_t buffer_length);
  /// Sends data to socket
  void Send(unsigned short port, const char *data, size_t data_length,
            const char *address = "127.0.0.1");

  int GetFd() { return fd_; }

 protected:
  /// Creates socket for UPD/IP connection
  Socket();
  /// Creates shared ptr on socket for UPD/IP connection based on file
  /// descriptor of existing already created socket()
  static std::shared_ptr<Socket> CreateSocket(int fd) {
    struct MakeSharedEnabler : public Socket {
      MakeSharedEnabler(int fd) : Socket(fd) {}
    };
    return std::make_shared<MakeSharedEnabler>(fd);
  }
  /// Initialize socket address structure for IPv4 internet protocol
  /// for further work with Berkeley sockets API
  static sockaddr_in InitializeSocketAddress(const char *address,
                                             unsigned short port);
  int fd_;

 private:
  explicit Socket(int fd);
  void Close();
};

}  // namespace ip
}  // namespace udp
}  // namespace s21

#endif  // CLIENT_SERVER_BERKELEY_SOCKETS_UDPIP_COMMON_SOCKET_H
