#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "User.hpp"

User::User() {}

User::User(const std::string &username, const std::string &password, double wallet)
{
    this->password = password;
    this->username = username;
    this->wallet = wallet;
}

User::User(const std::string &username, const std::string &password) {
    this->password = password;
    this->username = username;
    this->wallet = 0;
}

std::string User::getPassword()
{
    return this->password;
}

std::string User::getUsername()
{
    return this->username;
}

double User::getWallet()
{
    return this->wallet;
}

void User::setPassword(std::string password)
{
    this->password = password;
}

void User::setUsername(std::string username)
{
    this->username = username;
}

void User::setWallet(double wallet)
{
    this->wallet = wallet;
}
