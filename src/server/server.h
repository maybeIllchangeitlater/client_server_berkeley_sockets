#ifndef CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_SERVER_H
#define CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_SERVER_H

#include <vector>
#include <thread>
#include "acceptor.h"
#include "../common/socket.h"

namespace s21 {
    namespace tcp {
        namespace ip {
            class Server {
                explicit Server(unsigned short port);
            private:
                Acceptor acceptor_;
                std::vector<Socket> connections_;
                std::thread accept_thread_;
            };
        } //ip
    } //tcp
} //s21

#endif //CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_SERVER_H
