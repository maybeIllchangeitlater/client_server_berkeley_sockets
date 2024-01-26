#include "server.h"
#include <iostream>

namespace s21{
    namespace tcp{
        namespace ip{
            Server::Server(unsigned short port) : acceptor_(port) {
                accept_thread_ = std::thread([this](){
                    while (true){
                        try{
                            connections_.emplace_back(acceptor_.AsyncAccept().get());
                            std::cout << "new connection" << std::endl;
                            HandlePing(--connections_.end());
                        } catch (const std::exception &e){
                            std::cout << e.what() << std::endl;
                        }
                    }
                });
            }

            void Server::HandlePing(connections_iterator connection) {
                char buffer[1024];
                while (true) {
                    if((*connection)->Receive(buffer, sizeof(buffer)) > 0) {
                        std::string logged(Timestamper::GetTimestamp() + " " + buffer);
                        msg_que_.EmplaceBack(std::make_pair(connection, std::move(logged)));
                    } else {
                        std::cout << "connection closed by client";
                        connections_.erase(connection); //add mutex
                        break;
                    }
                }
            }
            Server::~Server() {
                accept_thread_.join();
                log_file_.close();
            }
        }
    }
}