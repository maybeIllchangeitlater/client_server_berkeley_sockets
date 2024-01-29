#include "socket.h"

namespace s21 {
namespace udp {
namespace ip {
Socket::Socket() {
  fd_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd_ == -1) {
    throw std::runtime_error("Socket constructor: Failed to create socket");
  }
}

Socket::Socket(int fd) { fd_ = fd; }

Socket::~Socket() { Close(); }

void Socket::Bind(unsigned short port, const char *address) {
    sockaddr_in addr = InitializeSocketAddress(address, port);
  if (bind(fd_, (sockaddr *)&addr, sizeof(addr)) == -1) {
    throw std::runtime_error("Socket constructor: Failed to bind socket");
  }
}

size_t Socket::Receive(char *buffer, size_t buffer_length) {
    int bytes_read = recvfrom(fd_, buffer, buffer_length, 0, NULL, 0);
    buffer[bytes_read] = '\0';
    return bytes_read;
}

void Socket::Send(unsigned short port, const char *data, size_t data_length, const char * address) {
    sockaddr_in server_address = InitializeSocketAddress(address, port);
    if(sendto(fd_, data, data_length, 0, (const struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        throw std::runtime_error("Failed to send data");
    };
}

void Socket::Close() {
  if (fd_ != -1) {
    close(fd_);
    fd_ = -1;
  }
}

sockaddr_in Socket::InitializeSocketAddress(const char *address,
                                            unsigned short port) {
  sockaddr_in addr;
  std::memset(&addr, 0, sizeof(addr));
  if (inet_pton(AF_INET, address, &addr.sin_addr.s_addr) <= 0) {
    throw std::runtime_error("Socket constructor: Failed to convert address");
  }
  addr.sin_port = htons(port);
  addr.sin_family = AF_INET;
  return addr;
}

}  // namespace ip
}  // namespace tcp
}  // namespace s21