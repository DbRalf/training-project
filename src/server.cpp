#include <udp_socket.h>
#include <udp_messages.h>
#include <iostream>
#include <cstring>
#include <thread>
#include <mutex>
#include <condition_variable>

//===============SERVER IS THE LOW===============//

std::string IP = "0.0.0.0";
int PORT {54321};

std::mutex m;
std::condition_variable cv;
bool got_first_msg = false;


void send_thread(UdpSocket &server_t,  PLATFORM_STATUS &platform){

    std::array <std::byte, 8> mes; 
    
    {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, []{return got_first_msg;}); 
    } 

    do{
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::lock_guard<std::mutex> lock(m);
        mes = platform.encode();
        std::cout << "\n======MESSAGE FOR SENDING======\n";
        platform.set();
        platform.print();

    }while(server_t.send(&mes));
}


// recive first time -> send + reciver at the same time mutex the mes so it will read anmd write to it properly

void recv_thread(UdpSocket &server_t, DRIVE_CMD &command){

    std::array <std::byte, 8> mes;
    
    
    
    while(server_t.recb(&mes)){

        std::lock_guard<std::mutex> lock(m);
        if(!got_first_msg){
            got_first_msg = true;
            cv.notify_one();
        }
        command.decode(mes);
        std::cout << "\n======RECIVED MESSAGE======\n";
        command.print();

    }
}


int main (){

    UdpSocket server_t(IP, PORT, true); // create a UDP server object 
    if(!server_t.open()) return 0;
    printf("succes full bind\n");

    DRIVE_CMD command;
    PLATFORM_STATUS platform;
    std::array <std::byte, 8> mes {};
    std::cout << "ready to recive mes\n";

    std::thread recv_loop(recv_thread, std::ref(server_t), std::ref(command));
    std::thread send_loop(send_thread, std::ref(server_t), std::ref(platform));

    recv_loop.join();
    send_loop.join();
    server_t.close();

    return 0;
}


