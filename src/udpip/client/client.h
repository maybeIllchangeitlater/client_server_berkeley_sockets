#ifndef UDPIP_CLIENT_H
#define UDPIP_CLIENT_H

#include <chrono>
#include <thread>
#include <string>
#include "../common/socket.h"

namespace s21 {
    namespace udp {
        namespace ip {
            class Client {
            public:
                Client(std::string name, unsigned short port);
                void Ping(std::chrono::seconds period);
            private:
                std::string name_;
                std::shared_ptr<Socket> sock_;
                unsigned short host_port_;
            };
        }
    }
}

#endif //UDPIP_CLIENT_H
