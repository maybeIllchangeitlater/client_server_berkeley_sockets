#ifndef CLIENT_SERVER_BERKELEY_SOCKETS_COMMON_SOCKET_H_
#define CLIENT_SERVER_BERKELEY_SOCKETS_COMMON_SOCKET_H_

#include <sys/socket.h>
#include <unistd.h> //for close()
#include <netinet/in.h> //for sockaddr_in
#include <arpa/inet.h> //inet_pton (converts addresses from text to binary)
#include <cstring> //for memset
#include <stdexcept>
#include <memory>

namespace s21 {
    namespace tcp {
        namespace ip {
            class MakeFromExisting;
            class Socket {
            public:
                ///Creates socket for TCP/IP connection
                Socket();
                Socket(const Socket&) = delete;
                Socket(Socket&& other) noexcept;
                Socket& operator=(const Socket&) = delete;
                Socket& operator=(Socket&& other) noexcept;
                ~Socket();
                ///binds sockets to address and port
                void Bind(const char * address, unsigned short port);
                ///binds socket to port on localhost. by default binds to whatever avaliable port given by OS
                void Bind(unsigned short port = 0);
//                operator int() const {
//                    return fd_;
//                }

            private:
                void Close();
                sockaddr_in InitializeSocketAddress(const char * address, unsigned short port);
            protected:
                int fd_;

                explicit Socket(int fd);
            };

        } //ip
    } //tcp
} // s21

#endif //CLIENT_SERVER_BERKELEY_SOCKETS_COMMON_SOCKET_H_
