# HIL UDP HANDLER (Cognata <-> Elbit M113 G12)

hardware in the loop integration between the Cognata station and the Elbit Systems autonomous APC.
Implement the UDP Interface for data and commands according to M113 G12 Platform CAN bus protocol

## what's in here
 -  UDP soket handler ('include/udp_socket.h', 'src/udp_socket.cpp')
 - messeage constructor and destructor ('include/udp_message.h', 'src/udp_message.cpp')


 ## Build

 makdir -p build
 cd build
 cmake ..
 cmake --build .


 ## example

 ./ still no examples :)