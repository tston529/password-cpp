#include <iostream> 
#include "password.hpp"

int main(int argc, char ** argv) {
    // used for quick testing how it handles previous
    // input via std::cin or scanf() 
    // (not well, without cin.ignore() to handle the extra newline
    // character, where getline works perfectly)
    if (argc > 1) { 
        std::string user;
        std::getline(std::cin, user);
        std::cout << "User: " << user << std::endl;
        // std::cin.ignore(10000, '\n');
    }

    std::cout << password::read_password() << std::endl;
    return 0; 
}
