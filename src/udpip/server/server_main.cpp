#include "server.h"

int main(){
    s21::udp::ip::Server server(8080);
    std::cout << "server is running press q to exit" << std::endl;
    while (std::getchar() != 'q'){
    }
    return 0;
}