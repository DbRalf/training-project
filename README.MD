# HIL UDP HANDLER (Cognata <-> Elbit M113 G12)

hardware in the loop integration between the Cognata station and the Elbit Systems autonomous APC.
Implement the UDP Interface for data and commands according to M113 G12 Platform CAN bus protocol

## what's in here
 - UDP soket handler ('include/udp_socket.h', 'src/udp_socket.cpp')
 - messeage: contained in an internal struct 
        constructor and destructor, 
        set - create a message from keyboard input
        get - pass enum for a specific value
        encode - encodes the struct to byte array
        decode - decodes a byte array to a struct
        print - prints the internal struct
        
        ('include/udp_message.h', 'src/udp_message.cpp')


 ## Build

 makdir -p build
 cd build
 cmake ..
 cmake --build .


 ## example

 ./ still no examples :)