#include <udp_socket.h>
#include <udp_messages.h>
#include <iostream>
#include <cstring>

std::string IP = "127.0.0.1";
int PORT {54321};

int main (){

    UdpSocket client_t(IP, PORT, false); // create a UDP client object 
    client_t.open();

    DRIVE_CMD drive;
    std::array <std::byte, 8> mes {};

    do{
        if(!drive.set()) break; // waits 1 sec for input (no input -> continue)
        mes = drive.encode();

        std::cout << "\n======SENT MESSAGE======\n";
        drive.print();
        // std::system("clear");

    } while (client_t.send(&mes));
    
    client_t.close();

    return 0;
}
