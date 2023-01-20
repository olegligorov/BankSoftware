#pragma once

#include "CommandExecutor.hpp"
#include <cmath>
#include <iomanip>
#include <regex>
#include <functional>

CommandExecutor::CommandExecutor(UserDatabase users)
{
    this->users = users;
}

std::string CommandExecutor::login()
{
    std::cout << "Enter username: ";
    std::string username;
    std::cin >> username;
    std::cout << "Enter password: ";
    std::string password;
    std::cin >> password;

    if (!users.hasUser(username))
    {
        return "Invalid username or password\n";
    }

    User currentUser;
    try
    {
        currentUser = users.getUser(username);
    }
    catch (...)
    {
        return "Invalid user\n";
    }

    std::hash<std::string> hashGenerator;
    std::string hashedPw = std::to_string(hashGenerator(password));

    if (currentUser.getPassword() != hashedPw)
    {
        return "Invalid password\n";
    }

    loggedUser = currentUser.getUsername();
    isLogged = true;
    return "Sucessfully logged in\n";
}

std::string CommandExecutor::logout()
{
    if (!isLogged)
    {
        return "You need to log in first\n";
    }
    isLogged = false;
    loggedUser = "";
    return "Successfully logged out\n";
}

std::string CommandExecutor::registerUser()
{
    std::cout << "Enter username: ";
    std::string username;
    std::cin >> username;

    if (users.hasUser(username))
    {
        return "Username is already taken\n";
    }

    std::cout << "Enter password\nThe password must have 5 or more characters, 1 lower case letter, \
1 upper case letter, 1 special character (!@#$%^&*):\n";
    std::string password;
    std::cin >> password;

    std::regex r("^(?=.{5,}$)(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&*]).*$");
    if (!regex_match(password, r)) {
        return "The password must have 5 or more characters, 1 lower case letter, \
1 upper case letter, 1 special character (!@#$%^&*)\n";
    }


    std::cout << "Confirm your password: ";
    std::string passwordConfirmation;
    std::cin >> passwordConfirmation;

    if (password != passwordConfirmation)
    {
        return "The confirmation doesn't match the password";
    }

    std::hash<std::string> hashGenerator;
    std::string hashedPw = std::to_string(hashGenerator(password));

    User newUser(username, hashedPw);
    loggedUser = newUser.getUsername();
    isLogged = true;
    users.registerUser(newUser);
    return "Sucessfully registered\n";
}

std::string CommandExecutor::executeCommand(std::string command)
{
    if (HELP == command)
    {
        return "Enter the input:\n\
    L - login\n\
    R - register\n\
    Q - quit\n\
After logging in:\n\
    C - Cancel account\n\
    D - Deposit\n\
    L - Logout\n\
    T - Transfer\n\
    W - Withrdraw\n";
    }
    if (REGISTER == command)
    {
        return registerUser();
    }
    if (LOGIN == command)
    {
        if (loggedUser != "")
        {
            return logout();
        }
        return login();
    }

    if ("Q" == command)
    {
        saveAccounts();
        return "";
    }

    if (loggedUser == "")
    {
        return "You need to log in first\n";
    }

    if (DELETE_ACCOUNT == command)
    {
        return deleteAccount();
    }
    if (DEPOSIT_MONEY == command)
    {
        return depositMoney();
    }
    if (TRANSFER == command)
    {
        return transferToUser();
    }
    if (WITHRDRAW == command)
    {
        return withrdraw();
    }
    return "Invalid command\n";
}

std::string CommandExecutor::deleteAccount()
{
    std::cout << "Enter your password: ";
    std::string password;
    std::cin >> password;
    try
    {
        if (password != users.getUser(loggedUser).getPassword())
        {
            return "Invalid username or password\n";
        }
    }
    catch (...)
    {
        return "Invalid username or password\n";
    }

    if (users.getUser(loggedUser).getWallet() == 0)
    {
        loggedUser == "";
        isLogged = false;
        users.deleteUser(loggedUser);
        return "Sucessfully deleted your account\n";
    }
    return "You can not delete your account if your balance is greater than 0\n";
}

std::string CommandExecutor::depositMoney()
{
    std::cout << "Enter the deposit amount: ";
    double depositAmount;
    std::cin >> depositAmount;

    return users.deposit(loggedUser, depositAmount);
}

std::string CommandExecutor::transferToUser()
{
    std::cout << "Enter the username of the user you want to transfer money to: ";
    std::string secondUsername;
    std::cin >> secondUsername;

    if (!users.hasUser(secondUsername))
    {
        return "Invalid user\n";
    }

    std::cout << "Enter the amount you want to transfer to " << secondUsername << ": ";
    double amount;
    std::cin >> amount;

    amount = std::ceil(amount * 100.0) / 100.0;

    return users.transferMoneyTo(loggedUser, secondUsername, amount);
}

std::string CommandExecutor::withrdraw()
{
    double amount;
    std::cout << "Enter the withrdraw amount: ";
    std::cin >> amount;

    amount = std::ceil(amount * 100.0) / 100.0;

    return users.withrdraw(loggedUser, amount);
}

std::string CommandExecutor::saveAccounts()
{
    users.writeAccountsInDatabase();
    return "Sucessfully saved the accounts into the datbase\n";
}
