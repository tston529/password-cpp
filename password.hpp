#include <unistd.h>
#include <stdio.h>  
#include <vector>
#include <iostream>
#include <climits>

std::string read_password()
{
    std::vector<char> v;
    std::cin.ignore(1);
    system("stty raw -echo"); 

    char input;
    while(1) {
        input = getchar(); 

        if (input == '\r') { // Carriage return
            break;
        } else if (input == 127) { // Backspace
            v.pop_back();
            printf("\b \b"); // Erase last '*'
            continue;
        }

        v.push_back(input);
        printf("*");
    }

    system("stty cooked"); 
    printf("\n");

    std::string str(v.begin(), v.end());
    return str; 
}

