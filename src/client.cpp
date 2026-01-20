#include <udp_socket.h>
#include <udp_messages.h>
#include <iostream>
#include <cstring>
#include <thread>
#include <mutex>
#include <condition_variable>


//===============CLIENT IS THE HIGH LEVEL===============//


std::string IP = "127.0.0.1";
int PORT {54321};
std::mutex m;


void send_thread(UdpSocket &client_t,  DRIVE_CMD &drive){

    std::array <std::byte, 8> mes; 
    keyboard_input ter1;

    do{
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        char key = ter1.get_input();
        std::lock_guard<std::mutex> lock(m);
        drive.set(key);
        mes = drive.encode();
        std::cout << "\n======MESSAGE FOR SENDING======\n";
        drive.print();

    }while(client_t.send(&mes));
}


// recive first time -> send + reciver at the same time mutex the mes so it will read anmd write to it properly

void recv_thread(UdpSocket &client_t, PLATFORM_STATUS &status){

    std::array <std::byte, 8> mes;

    while(client_t.recb(&mes)){

        std::lock_guard<std::mutex> lock(m);
        status.decode(mes);
        std::cout << "\n======RECIVED MESSAGE======\n";
        status.print();

    }
}


int main (){

    UdpSocket client_t(IP, PORT, false); // create a UDP client object 
    client_t.open();

    DRIVE_CMD drive;
    PLATFORM_STATUS status;
    std::array <std::byte, 8> mes {};

    std::thread recv_loop(recv_thread, std::ref(client_t), std::ref(status));
    std::thread send_loop(send_thread, std::ref(client_t), std::ref(drive) );

    recv_loop.join();
    send_loop.join();
    client_t.close();

    return 0;
}
