#ifndef CLIENT_SERVER_BERKELEY_SOCKETS_CLIENT_CLIENT_H
#define CLIENT_SERVER_BERKELEY_SOCKETS_CLIENT_CLIENT_H

#include <string>
#include <thread>
#include <chrono>
#include "../common/socket.h"

namespace s21 {
    namespace tcp {
        namespace ip {
            class Client : protected Socket{
            public:
                ///creates client on localhost + whatever port is given by OS
                Client(const std::string &client_name);
                ///connects to remote host
                void Connect(unsigned short port, const char * address = "127.0.0.1");
                ///pings server every period seconds. Ping only sends client's name
                void PingServerPeriodically(const std::chrono::seconds &period);
            private:
                std::string client_name_;
            };
        } //ip
    } //tcp
} //s21

#endif //CLIENT_SERVER_BERKELEY_SOCKETS_CLIENT_CLIENT_H
