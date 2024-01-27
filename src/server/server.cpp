#include "server.h"
#include <iostream>

namespace s21{
    namespace tcp{
        namespace ip{
            Server::Server(unsigned short port) : acceptor_(port) {
                log_file_ = std::ofstream("log.txt");
                accept_thread_ = std::thread([this](){
                    while (true){
                        try{
                            auto connection = acceptor_.AsyncAccept().get();
                            if (connection){
                                std::thread([this, connection](){
                                    HandlePing(connection);
                                }).detach();
                            }
                        } catch (const std::exception &e){
                            std::cout << e.what() << std::endl;
                        }
                    }
                });
                accept_thread_.detach();
//                write_to_log_thread_ = std::thread([this](){
                    while (true) {
                        LogFromQue();
                    }
//                });
//                write_to_log_thread_.join();
            }

            void Server::HandlePing(std::shared_ptr<Socket> connection) {
                std::cout << "new connection" << std::endl;
                char buffer[1024];
                while (true) {
                    if(connection->Receive(buffer, sizeof(buffer)) > 0) {
                        std::string logged(Timestamper::GetTimestamp() + " " + buffer + "\n");
                        msg_que_.EmplaceBack(std::move(logged));
                    } else {
                        std::cout << "connection closed by client" << std::endl;
                        break;
                    }
                }
            }

            void Server::LogFromQue() {
                msg_que_.Wait();
                std::cout << msg_que_.PopFront();
            }

            Server::~Server() {
                accept_thread_.join();
                log_file_.close();
            }
        }
    }
}