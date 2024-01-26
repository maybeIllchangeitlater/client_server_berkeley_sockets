#ifndef CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_ACCEPTOR_H_
#define CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_ACCEPTOR_H_

#include "../common/socket.h"
#include <future>

namespace s21{
    namespace tcp {
        namespace ip {
            ///Acceptor socket for server. Responsible for accepting connections
            class Acceptor : protected Socket{
            public:
                constexpr static const short BACKLOG_LIMIT = 128;
                ///creates Acceptor sockets and binds it to port
                ///Acceptor immediately starts listening on specified port
                explicit Acceptor(unsigned short port) : Socket(){
                    Bind(port);
                    if(listen(fd_, BACKLOG_LIMIT) == -1){
                        throw std::runtime_error("Acceptor: failed to listen on port " + std::to_string(port));
                    }
                }
                ///Asynchronously accepts connections
                std::future<std::shared_ptr<Socket>> AsyncAccept() {
                    return std::async(std::launch::async, [this]() {
                        return Accept();
                    });
                }
                ///Accepts connection and returns shared ptr to socket object for it
                std::shared_ptr<Socket> Accept(){
                    sockaddr_in client_address;
                    socklen_t addr_len = sizeof(client_address);
                    std::memset(&client_address, 0, addr_len);
                    int client_fd = accept(fd_, (sockaddr*)&client_address, &addr_len);
                    if (client_fd == -1) {
                        throw std::runtime_error("Socket accept: Failed to accept connection");
                    }
                    return CreateSocket(client_fd);
                }

            };
        } //ip
    } //tcp
} //s21

#endif //CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_ACCEPTOR_H_