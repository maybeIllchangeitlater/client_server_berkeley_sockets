#include "server.h"

namespace s21 {
namespace tcp {
namespace ip {
Server::Server(unsigned short port) : log_file_("log.txt"), acceptor_(port) {
  InitializeAcceptThread();
  InitializeLoggingThread();
}

Server::~Server() {
  if (accept_thread_.joinable()) {
    accept_thread_.join();
  }
  if (write_to_log_thread_.joinable()) {
    write_to_log_thread_.join();
  }
  log_file_.close();
}

void Server::HandlePing(std::shared_ptr<Socket> connection) {
  char buffer[1024];
  while (true) {
    if (connection->Receive(buffer, sizeof(buffer)) > 0) {
      std::string logged(Timestamper::GetTimestamp() + " " + buffer);
      msg_que_.EmplaceBack(std::move(logged));
    } else {
      break;
    }
  }
}

void Server::LogFromQue() {
  msg_que_.Wait();
  log_file_ << msg_que_.PopFront() << std::endl;
}

void Server::InitializeAcceptThread() {
  accept_thread_ = std::thread([this]() {
    while (true) {
      try {
        auto connection = acceptor_.AsyncAccept().get();
        if (connection) {
          std::thread([this, connection]() {
            HandlePing(connection);
          }).detach();
        }
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
      }
    }
  });
  accept_thread_.detach();
}

void Server::InitializeLoggingThread() {
  write_to_log_thread_ = std::thread([this]() {
    while (true) {
      LogFromQue();
    }
  });
  write_to_log_thread_.detach();
}

}  // namespace ip
}  // namespace tcp
}  // namespace s21