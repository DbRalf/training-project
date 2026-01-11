#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <iostream>
#include <vector>

class keyboard_input
{
public:
    keyboard_input();
    ~keyboard_input();

    char get_input();    

private:
    termios old_ter {};                                         // create a struct to hold terminal settings
    int old_flags;
    fd_set readfds;                                             //bitmask fd

};

#endif