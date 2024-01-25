#include "socket.h"

namespace s21 {
  namespace tcp{
      namespace ip{
          Socket::Socket(){
              fd_ = socket(AF_INET, SOCK_STREAM, 0);
              if(fd_ == -1){
                  throw std::runtime_error("Socket constructor: Failed to create socket");
              }
          }
          Socket::Socket(Socket &&other) noexcept {
              fd_ = other.fd_;
              other.fd_ = -1;
          }
          Socket& Socket::operator=(Socket &&other) noexcept{
              Close();
              fd_ = other.fd_;
              other.fd_ = -1;
              return *this;
          }
          Socket::Socket(int fd) {
              fd_ = fd;
          }

          Socket::~Socket(){
              Close();
          }

          void Socket::Bind(const char * address, unsigned short port) {
              sockaddr_in addr = InitializeSocketAddress(address, port);
              if(bind(fd_, (sockaddr*)&addr, sizeof(addr)) == -1){
                  throw std::runtime_error("Socket constructor: Failed to bind socket");
              }
          }

          void Socket::Bind(unsigned short port) {
              Bind("127.0.0.1", port);
          }

//          void Socket::Connect(const char *address, unsigned short port) {
//              sockaddr_in server_address = InitializeSocketAddress(address, port);
//              if (connect(fd_, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
//                  throw std::runtime_error("Socket connect: Failed to connect to server");
//              }
//          }
          void Socket::Close() {
              if(fd_ != -1) {
                  close(fd_);
              }
          }
          sockaddr_in Socket::InitializeSocketAddress(const char *address, unsigned short port) {
              sockaddr_in addr;
              std::memset(&addr, 0, sizeof(addr));
              if(inet_pton(AF_INET, address, &addr.sin_addr.s_addr)  <= 0) {
                  throw std::runtime_error("Socket constructor: Failed to convert address");
              }
              addr.sin_port = htons(port);
              addr.sin_family = AF_INET;
              return addr;
          }

      }
  }
}