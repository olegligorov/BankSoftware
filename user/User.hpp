#ifndef USER_H
#define USER_H

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class User
{
private:
    std::string password;
    std::string username;

    double wallet;

public:
    User();

    User(const std::string &username, const std::string &password, double wallet);

    User(const std::string &username, const std::string &password);

    std::string getPassword();

    std::string getUsername();

    double getWallet();

    void setPassword(std::string password);

    void setUsername(std::string username);

    void setWallet(double wallet);
};
#endif