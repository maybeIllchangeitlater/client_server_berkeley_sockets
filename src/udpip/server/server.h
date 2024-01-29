#ifndef CLIENT_SERVER_BERKELEY_SOCKETS_UDPIP_SERVER_SERVER_H
#define CLIENT_SERVER_BERKELEY_SOCKETS_UDPIP_SERVER_SERVER_H

#include <fstream>
#include <thread>
#include <memory>
#include <string>
#include <list>
#include "../common/socket.h"
#include "../common/timestamper.h"
#include "../../tcpip/common/thread_safe_que.h"

namespace s21 {
    namespace udp {
        namespace ip {
            class Server {
            public:
                explicit Server(unsigned short port);
                ~Server();
                Server(const Server &other) = delete;
                Server(Server &&other) = delete;
                Server &operator=(const Server &other) = delete;
                Server &operator=(Server &&other) = delete;

                void Listen();
                
            private:
                void CreateNewListenThread();
                bool OnlyOneListenThread();
                void HandleNewMessage();
                void HandleThreadFinished();

            private:
                std::ofstream log_file_;
                s21::ThreadSafeQ<std::string> msg_que_;
                std::condition_variable cv_;
                std::mutex listen_mutex_;
                std::mutex cv_mutex_;
                std::list<std::thread> listen_threads_;
                std::thread handle_thread_;
                std::shared_ptr<Socket> sock_;
            };
        } //ip
    } //udp
} // s21

#endif //CLIENT_SERVER_BERKELEY_SOCKETS_UDPIP_SERVER_SERVER_H
