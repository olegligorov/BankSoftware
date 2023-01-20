#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <cstring>
#include <iostream>
#include <string>
#include <deque>
// #include "../user/User.cpp"
#include "../user/UserDatabase.hpp"

class CommandExecutor {
private:
    UserDatabase users;
    const std::string LOGIN = "L";
    const std::string REGISTER = "R";
    const std::string QUIT = "Q";

    const std::string DELETE_ACCOUNT = "C";
    const std::string DEPOSIT_MONEY = "D";
    const std::string BACK_TO_MAIN_MENU = "L";
    const std::string TRANSFER = "T";
    const std::string WITHRDRAW = "W";
    const std::string HELP = "help";
    
    std::string loggedUser = "";
    bool isLogged = false;
public:
    CommandExecutor(UserDatabase users);

    std::string executeCommand(std::string message);
    std::string deleteAccount();

    std::string depositMoney();
    std::string transferToUser();
    std::string withrdraw();
    std::string login();
    std::string logout();
    std::string registerUser();
    std::string saveAccounts();
};  

#endif