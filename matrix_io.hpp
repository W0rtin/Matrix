#pragma once

#include <iostream>
#include <termios.h>
#include <unistd.h>

inline void clear_t() {
    std::cout << "\033c";
}

inline int getch() {
    termios oldt{};
    termios newt{};
    int ch = 0;

    if (tcgetattr(STDIN_FILENO, &oldt) != 0) return 27;
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) != 0) return EOF;
    ch = ::getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

