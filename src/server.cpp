#include <udp_socket.h>
#include <udp_messages.h>
#include <iostream>
#include <cstring>


std::string IP = "0.0.0.0";
int PORT {54321};
int main (){

    UdpSocket server_t(IP, PORT, true); // create a UDP server object 
    if(!server_t.open()) return 0;
    printf("succes full bind\n");

    PLATFORM_STATUS platform;
    std::array <std::byte, 8> mes {};
    std::cout << "ready to recive mes\n";

    while(server_t.recb(&mes)){

        platform.decode(mes);
        std::cout << "\n======RECIVED MESSAGE======\n";
        platform.print();

    }

    server_t.close();

    return 0;
}


