#include "acceptor.h"

namespace s21{
    namespace tcp{
        namespace ip{
            Acceptor::Acceptor(unsigned short port) : Socket(){
                Bind(port);
                if(listen(fd_, 128) == -1){
                    throw std::runtime_error("Acceptor: failed to listen on port " + std::to_string(port));
                }
            }

            std::shared_ptr<Socket> Acceptor::Accept() {
                sockaddr_in client_address;
                socklen_t addr_len = sizeof(client_address);
                std::memset(&client_address, 0, addr_len);
                int client_fd = accept(fd_, (sockaddr*)&client_address, &addr_len);
                if (client_fd == -1) {
                    throw std::runtime_error("Socket accept: Failed to accept connection");
                }
                return CreateSocket(client_fd);
            }

            std::future<std::shared_ptr<Socket>> Acceptor::AsyncAccept() {
                return std::async(std::launch::async, [this]() {
                    return Accept();
                });
            }
        } //ip
    } //tcp
} //s21