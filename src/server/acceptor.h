#ifndef CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_ACCEPTOR_H_
#define CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_ACCEPTOR_H_

#include "../common/socket.h"
#include <future>

namespace s21{
    namespace tcp {
        namespace ip {
            class Acceptor : protected Socket{
            public:
                explicit Acceptor(unsigned short port);
                std::shared_ptr<Socket> Accept();
                std::future<std::shared_ptr<Socket>> AsyncAccept();
            };
        } //ip
    } //tcp
} //s21

#endif //CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_ACCEPTOR_H_