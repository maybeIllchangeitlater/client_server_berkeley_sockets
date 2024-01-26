#ifndef CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_SERVER_H
#define CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_SERVER_H

#include <list>
#include <thread>
#include <fstream>
#include "acceptor.h"
#include "../common/socket.h"
#include "../common/timestamper.h"
#include "../common/thread_safe_que.h"

namespace s21 {
    namespace tcp {
        namespace ip {
            class Server {
            public:
                using connections_iterator = std::list<std::shared_ptr<Socket>>::iterator;
                explicit Server(unsigned short port);
                ~Server();
            private:
                void HandlePing(connections_iterator connection);
            private:
                Acceptor acceptor_;
                std::list<std::shared_ptr<Socket>> connections_;
                s21::ThreadSafeQ<std::pair<connections_iterator, std::string>> msg_que_;
                std::thread accept_thread_;
                std::ofstream log_file_;
            };
        } //ip
    } //tcp
} //s21

#endif //CLIENT_SERVER_BERKELEY_SOCKETS_SERVER_SERVER_H
