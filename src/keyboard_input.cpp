#include <keyboard_input.h>

keyboard_input::keyboard_input(){

    tcgetattr(STDIN_FILENO, &old_ter);                          // get the terminal settings
    termios new_ter = old_ter;
    new_ter.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO)); // change the setting of the echo and canonical mode of the terminal
    new_ter.c_cc[VMIN] = 1;                                     // how many bits to read
    new_ter.c_cc[VTIME] = 1;                                    //how much time to wait in read
    tcsetattr(STDIN_FILENO, TCSANOW, &new_ter);                 // applay the changes

    old_flags = fcntl(STDIN_FILENO, F_GETFL, 0);            // record the original terminal flags
    fcntl(STDIN_FILENO, F_SETFL, old_flags | O_NONBLOCK);
}


keyboard_input::~keyboard_input()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old_ter);
    fcntl(STDIN_FILENO, F_SETFL, old_flags);  
}


char keyboard_input::get_input(){

    FD_ZERO(&readfds);                                          // clear
    FD_SET(STDIN_FILENO, &readfds);                             // set the terminal for keyboard

    // timeval sets time to wait for select
    timeval tv{};                                               // create struct of timeval
    tv.tv_sec = 2;                                              // set second to timeout
    tv.tv_usec = 0;                                           // set microsecond to timeout
 
    // first parm - is the last file descriptor +1
    int ready = select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &tv);
    char ch;
    if(ready > 0 && FD_ISSET(STDIN_FILENO, &readfds)){
        // an input is detected
        read(STDIN_FILENO, &ch, 1);
        return ch; 
    }
    else if (ready == 0){
        ch = '\0';
        return ch;
    }
    else{
        std::cerr << "trouble with input\n";
        ch = '\e';
        return ch;
    }
    
} 
