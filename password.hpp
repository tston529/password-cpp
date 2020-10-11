#include <stdio.h>  
#include <vector>
#include <iostream>
#include <climits>
// #include <stropts.h>

#ifdef WIN32
#include <windows.h>
#include <io.h> // _setmode
#include <fcntl.h> // _O_BINARY
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace password
{
    int SetStdinEcho(bool enable=true)
    {
    #ifdef WIN32
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hStdin, &mode);

        int changed_mode = 0;
        if (!enable) {
            mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);

            // Handle input as binary, prevents conversion of "CR" to "CRLF" so <ENTER> works properly.
            // Prevents Unicode from being entered, as a result.
            int changed_mode = _setmode(_fileno(stdin), _O_BINARY);
            if (changed_mode == -1) {
                mode |= (ENABLE_LINE_INPUT);
            }
        }       
        else
            mode |= (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
            

        SetConsoleMode(hStdin, mode); 

        return changed_mode;

    #else
        struct termios tty;
        tcgetattr(STDIN_FILENO, &tty);
        if (!enable)
            tty.c_lflag &= ~(ICANON | ECHO);
        else
            tty.c_lflag |= (ICANON | ECHO);

        (void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
        return 0;
    #endif
    }

    std::string read_password()
    {
        int use_asterisks = SetStdinEcho(false); // Prevent input from rendering
        if (use_asterisks != -1) {
            std::cin >> std::skipws;
            std::vector<char> v;

            char input;
            while (1) {
                input = getchar();
                // std::cerr <<"input: "<< (int)input << std::endl;

                if (input == '\r' || input == '\n') { // Carriage return
                    break;
                }
                else if (input == 127 || input == '\b') { // Backspace
                    v.pop_back();
                    printf("\b \b"); // Erase last '*'
                    continue;
                }

                v.push_back(input);
                fprintf(stderr, "*");
            }

            SetStdinEcho(true); // Re-enable input rendering
            printf("\x1b[0G");

            return std::string(v.begin(), v.end());
        }

        SetStdinEcho(true); // Re-enable input rendering
        std::string input;
        std::cin >> input;
        return input;
        
    }
}

