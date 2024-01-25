#include "acceptor.h"

int main(){
    s21::tcp::ip::Acceptor acceptor(5050);
    acceptor.AsyncAccept();
    return 0;
}