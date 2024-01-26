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
                Client(const std::string &client_name);
                void Connect(unsigned short port, const char * address = "127.0.0.1");
                void PingServerPeriodically(const std::chrono::seconds &period);
            private:
                std::string client_name_;
            };
        } //ip
    } //tcp
} //s21

#endif //CLIENT_SERVER_BERKELEY_SOCKETS_CLIENT_CLIENT_H
