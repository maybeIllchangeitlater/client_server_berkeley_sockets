#include "client.h"

namespace s21{
    namespace tcp{
        namespace ip{
            Client::Client(const std::string &client_name) : Socket(), client_name_(client_name) {
                Bind();
            }

            void Client::Connect(unsigned short port, const char *address) {
                sockaddr_in server_address = InitializeSocketAddress(address, port);
              if (connect(fd_, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
                  throw std::runtime_error("Socket connect: Failed to connect to server");
              }
            }

            void Client::PingServerPeriodically(const std::chrono::seconds &period) {
                while (true) {
                    Send(fd_, client_name_.c_str(), client_name_.size());
                    std::this_thread::sleep_for(std::chrono::seconds(period));
                }
            }
        }
    }
}
