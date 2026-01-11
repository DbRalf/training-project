#include <iostream>
#include <string>
#include <cstring>      // For memset
#include <unistd.h>     // For close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdint>
#include <type_traits>
#include <ifaddrs.h>
#include <udp_socket.h>

// Optional: for better error reporting
#include <errno.h>


/* 
    This file contains definitions for UDP communication structures 
    the class contains methods for udp socket handeling and message sending/receiving

    
*/




UdpSocket::UdpSocket(const std::string& ip, uint16_t port, bool is_server)
    :m_ip {ip}, m_port {port}, m_fd {-1}, m_open {false}, m_is_server{is_server}, m_dest_set{false}
{
    //clear struct from junk
    std::memset(&m_dest, 0 , sizeof(m_dest));
    std::memset(&m_local, 0 , sizeof(m_local));

    if(!m_is_server){
        m_dest.sin_family = AF_INET;
        m_dest.sin_port = htons(m_port);
    }
    
    
    if(m_is_server){
        m_local.sin_family = AF_INET;
        m_local.sin_port = htons(m_port);
        m_local.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    
}


bool UdpSocket::open(){

    if(m_open){                                             // cheack if the socket had been opened
        std::cerr << "the socket is allready open";
        return false;
    }

    if(m_ip.empty() && ! m_is_server){                      // check ip 
        std::cerr << "no ip is given\n";
        return false;
    }
    
    if(!m_is_server){                                       // for clients
        if(inet_pton(AF_INET, m_ip.c_str(), &m_dest.sin_addr) != 1){
            std::cerr << "invalid ip\n";
            return false;
        }
        m_dest_set = true;
    }
    
    

    m_fd = socket(AF_INET, SOCK_DGRAM, 0);                 // open socket
    if(m_fd < 0) {
        std::cerr << "unable to create socket\n";
        return false;
    }
    
    if(!m_is_server){
        m_open = true;
        return true;
    } 

    if(bind(m_fd, reinterpret_cast<sockaddr*> (&m_local), sizeof(m_local)) == -1){
        std::cerr << "binding failed\n";
        close();
        return false;
    }

    m_open = true;
    return true;
}

void UdpSocket::close(){

    if(!m_open) return;

    if(m_fd >= 0){
        ::close(m_fd);                                   // close file descriptor
        m_fd = -1;
    }
    m_open = false;
    m_dest_set =false;          
}


ssize_t UdpSocket::recb(void* buffer, size_t len){

    if(!m_open){
        std::cerr <<"socket isn't open\n";
        return -1;
    }

    sockaddr_in sender {};
    socklen_t sender_len = sizeof(sender);

    ssize_t recvd = recvfrom(                           // wait for a packet
            m_fd,                                       // socket
            buffer,                                     // where to store byte data
            len,                                        // max to read
            0,                                          // flags
            reinterpret_cast<sockaddr*>(&sender),       // where to store sender data
            &sender_len                                 // its length
            );

    if(recvd < 0){
        std::cerr << "failed reciving\n";
        return -1;
    }

    if(m_is_server){
        m_dest = sender;
        m_dest_set = true;

    }

    return recvd;                                       // return the bytes reciced  
                                                        
}   



bool UdpSocket::send(const void* data, size_t len){

    if(!m_open){
        std::cerr << "the socket is not open\n";
        return false;
    }

    if(!m_dest_set) return false; 

    socklen_t dest_len = sizeof(m_dest);
    ssize_t sendb = sendto(                             // send byts
            m_fd,                                       // socket
            data,                                       // message in bytes
            len,                                        // length of the message
            0,                                          // flags
            reinterpret_cast<sockaddr*>(&m_dest),       // send to .. 
            dest_len                                    // size of the struct
            );
    
    if(sendb < 0){
        std::cerr << "sending failed\n";
        return false;
    }
                                                         
    return static_cast<size_t>(sendb) == len;           // check if the sent bytes are equal to the message len
}

UdpSocket::~UdpSocket(){

    close();
}


