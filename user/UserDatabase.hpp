#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "User.hpp"

class UserDatabase {
private:
    std::unordered_map<std::string, User> users;
    std::string database = "users.txt";
    void readFromDatabase();
public:
    UserDatabase(std::string UserDatabase);
    UserDatabase();
    void registerUser(User user);
    void writeAccountsInDatabase();
    User getUser(std::string username);
    bool hasUser(std::string username);
    void deleteUser(std::string username);
    std::string deposit(std::string username, double amount);
    std::string transferMoneyTo(std::string sender, std::string receiver, double amount);
    std::string withrdraw(std::string username, double amount);
};
#endif
