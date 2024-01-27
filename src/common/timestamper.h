#ifndef CLIENT_SERVER_BERKELEY_SOCKETS_COMMON_TIMESTAMPER_H
#define CLIENT_SERVER_BERKELEY_SOCKETS_COMMON_TIMESTAMPER_H

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace s21 {
struct Timestamper {
  /// Create timestamp with format [%Y-%m-%d %H:%M:%S.%3f] based on current time
  static std::string GetTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                            now.time_since_epoch()) %
                        1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "[%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << milliseconds.count()
       << "]";

    return ss.str();
  }
};
}  // namespace s21

#endif  // CLIENT_SERVER_BERKELEY_SOCKETS_COMMON_TIMESTAMPER_H
