#include <stdio.h>  
#include <vector>
#include <iostream>
#include <climits>

#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace password
{
    void SetStdinEcho(bool enable=true)
    {
    #ifdef WIN32
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hStdin, &mode);

        if (!enable)
            mode &= ~ENABLE_ECHO_INPUT;
        else
            mode |= ENABLE_ECHO_INPUT;

        SetConsoleMode(hStdin, mode);

    #else
        struct termios tty;
        tcgetattr(STDIN_FILENO, &tty);
        if (!enable) {
            tty.c_lflag &= ~ICANON;
            tty.c_lflag &= ~ECHO;
        }
        else {
            tty.c_lflag |= ICANON;
            tty.c_lflag |= ECHO;
        }

        (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    #endif
    }

    std::string read_password()
    {
        // The most recent character was a newline and might be
        // rendered as '*', so flush the input buffer before any
        // rendering to remove this.
        std::cin.clear();       
        std::cin.ignore(INT_MAX, '\n');

        SetStdinEcho(false); // Prevent input from rendering
        
        std::vector<char> v;
        
        char input;
        while(1) {
            input = getchar(); 

            if (input == '\r' || input  == '\n') { // Carriage return
                break;
            } else if (input == 127) { // Backspace
                v.pop_back();
                printf("\b \b"); // Erase last '*'
                continue;
            }

            v.push_back(input);
            printf("*");
        }
        
        SetStdinEcho(true); // Re-enable input rendering
        printf("\n");

        return std::string(v.begin(), v.end()); 
    }
}

