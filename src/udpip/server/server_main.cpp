#include "server.h"

int main(){
    s21::udp::ip::Server server(8080);
    server.Listen();
    while (true){

    }
    return 0;
}