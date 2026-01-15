#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <sys/types.h>
#include <netinet/in.h>


// UdpSocket.h (single-file example)
  

    class UdpSocket {
    public:
        UdpSocket(const std::string& ip, uint16_t port, bool is_server);
        ~UdpSocket(); 

        bool open();                 // create socket
        void close();                // close socket
        bool send(const std::array <std::byte, 8>* data);
        bool recb(std::array <std::byte, 8>* buffer);

    private:
        int m_fd;                    // socket file descriptor
        bool m_is_server;            // for binding
        bool m_open;                 // is socket open?
        bool m_dest_set;             // flag set ip
        std::string m_ip;            // destination IP
        std::uint16_t m_port;             // destination port

    

        // address structs kept private (details hidden)
        struct sockaddr_in m_dest;  // to send 
        struct sockaddr_in m_local; // client
  };


  #endif

  