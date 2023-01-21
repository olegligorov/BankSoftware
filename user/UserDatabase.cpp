#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "User.hpp"
#include <fstream>
#include "UserDatabase.hpp"

void UserDatabase::readFromDatabase()
{
    std::ifstream fin;
    fin.open(database); 
    if (!fin)
    {
        //the file doesn't exist
        std::ofstream { database };
        std::cout << "The database didn't exist and now is created\n";
    }

    std::vector<User> databaseUsers;
    User temp;
    std::string username;
    std::string password;
    double wallet;

    while (fin >> username >> password >> wallet)
    {
        temp.setUsername(username);
        temp.setPassword(password);
        temp.setWallet(wallet);
        databaseUsers.push_back(temp);
    }

    for (auto &user : databaseUsers)
    {
        users[user.getUsername()] = user;
    }
    fin.close();
}

UserDatabase::UserDatabase(std::string database)
{
    this->database = database;
    readFromDatabase();
}

UserDatabase::UserDatabase()
{
    this->database = "users.txt";
    readFromDatabase();
}

void UserDatabase::registerUser(User user)
{
    users.insert({user.getUsername(), user});
}

void UserDatabase::writeAccountsInDatabase()
{
    // std::cout << "Saving accounts in database\n";
    std::ofstream fout;
    fout.open(database);
    if (!fout)
    {
        throw std::invalid_argument("Error in opening the output file\n");
    }
    for (auto &kv : users)
    {
        fout << kv.second.getUsername() << ' ' << kv.second.getPassword() << ' ' << kv.second.getWallet() << '\n';
    }
    fout.close();
}

User UserDatabase::getUser(std::string username)
{
    if (users.count(username))
    {
        return users[username];
    }
    throw std::invalid_argument("User does not exist\n");
}

bool UserDatabase::hasUser(std::string username)
{
    return users.count(username) > 0;
}

void UserDatabase::deleteUser(std::string username)
{
    users.erase(username);
}

std::string UserDatabase::deposit(std::string username, double amount)
{
    if (amount < 0)
    {
        return "The deposit amount has to be a positive number\n";
    }
    amount = std::ceil(amount * 100.0) / 100.0;
    users[username].setWallet(users[username].getWallet() + amount);
    return "Sucessfully deposited " + std::to_string(amount) + " $\n";
}

std::string UserDatabase::transferMoneyTo(std::string sender, std::string receiver, double amount)
{
    if (amount < 0)
    {
        return "The transfer amount can not be a negative number";
    }

    if (users[sender].getWallet() + 10000 < amount)
    {
        return "Overdraft can not be greater than 10000$\n";
    }

    users[sender].setWallet(users[sender].getWallet() - amount);
    users[receiver].setWallet(users[receiver].getWallet() + amount);
    return "Sucessfully transfered " + std::to_string(amount) + "$ to " + receiver + "\n";
}

std::string UserDatabase::withrdraw(std::string username, double amount)
{
    if (amount < 0)
    {
        return "Withtrdraw amount can not be a negative number";
    }

    if (users[username].getWallet() + 10000 < amount)
    {
        return "Overdraft can not be greater than 10000$\n";
    }
    users[username].setWallet(users[username].getWallet() - amount);
    return "Sucessfully withdrew " + std::to_string(amount) + "$\n";
}
