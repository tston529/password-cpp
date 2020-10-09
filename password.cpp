#include <iostream> 
#include "password.hpp"

int main() { 
    std::cout << "Enter your username: " << std::endl;
    std::string user;
    std::cin >> user;

    std::cout << "Enter your password: " << std::endl;
    std::string pass = password::read_password();

    std::cout << "User: \"" << user << "\"" << "\nPass: \"" << pass << "\"" << std::endl;
    return 0; 
}
