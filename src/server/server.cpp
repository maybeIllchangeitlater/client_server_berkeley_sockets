#include "server.h"
#include <iostream>

namespace s21{
    namespace tcp{
        namespace ip{
            Server::Server(unsigned short port) : acceptor_(port) {
                accept_thread_ = std::thread([this](){
                    while (true){
                        try{
                            Socket new_connection = acceptor_.AsyncAccept().get();
                            connections_.emplace_back(std::move(new_connection));
                        } catch (const std::exception &e){
                            std::cout << e.what();
                        }
                    }
                });
            }
        }
    }
}