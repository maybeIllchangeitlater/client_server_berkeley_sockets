#include "server.h"
#include <iostream>

namespace s21{
    namespace udp{
        namespace ip{
            Server::Server(unsigned short port) : log_file_("log.txt"), sock_(Socket::CreateSocket()){
                sock_->Bind(port);
                CreateNewListenThread();
                handle_thread_ = std::thread([this](){ while(true){HandleNewMessage();}});
                handle_thread_.detach();
                while (true) {
                    HandleThreadFinished();
                }
            }

            Server::~Server() {
                for(auto &thread : listen_threads_){
                    if(thread.joinable()){
                        thread.join();
                    }
                }
                if(handle_thread_.joinable()){
                    handle_thread_.join();
                }
            }

            void Server::Listen() {
                char buffer[128];
                size_t pings_per_second = 0;
                auto ping_timer = std::chrono::high_resolution_clock::now();
                while (OnlyOneListenThread() || pings_per_second != 0) {
                    if (sock_->Receive(buffer, 128) > 0) {
                        msg_que_.EmplaceBack(s21::Timestamper::GetTimestamp() + " " + buffer);
                        if(std::chrono::high_resolution_clock::now() - ping_timer > std::chrono::seconds(1)){
                            ping_timer = std::chrono::high_resolution_clock::now();
                            pings_per_second = 1;
                        }else {
                            ++pings_per_second;
                        }
                        if(pings_per_second >= 10){
                            CreateNewListenThread();
                        }
                    }
                }
                cv_.notify_one();
            }


            void Server::CreateNewListenThread() {
                std::lock_guard<std::mutex> lock(listen_mutex_);
                listen_threads_.emplace_back();
                listen_threads_.back() = std::thread([this]() { Listen(); });
                listen_threads_.back().detach();
            }

            bool Server::OnlyOneListenThread() {
                std::lock_guard<std::mutex> lock(listen_mutex_);
                return listen_threads_.size() == 1;
            }

            void Server::HandleNewMessage() {
                msg_que_.Wait();
                log_file_ << msg_que_.PopFront() << std::endl;
            }

            void Server::HandleThreadFinished() {
                std::unique_lock<std::mutex> ul(cv_mutex_);
                cv_.wait(ul, [this](){
                    return std::any_of(listen_threads_.begin(), listen_threads_.end(),
                                       [](const std::thread& t) { return !t.joinable(); });
                });
                std::lock_guard<std::mutex> lock(listen_mutex_);
                listen_threads_.erase(
                        std::remove_if(listen_threads_.begin(), listen_threads_.end(),
                                       [](const std::thread& t){ return !t.joinable(); }),
                                       listen_threads_.end());
            }

        }
    }
}