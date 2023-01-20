#include <iostream>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "commands/CommandExecutor.hpp"
// #include "commands/CommandExecutor.cpp"

class BankSoftware
{
private:
    UserDatabase users;
    CommandExecutor *commandExecutor = new CommandExecutor(users);

public:
    BankSoftware() = default;

    void run()
    {
        std::cout << "The bank software is running\n";
        std::cout << "Type help to view all the commands\n";
        while (true)
        {
            std::string command;
            std::cin >> command;
            if (command == "Q")
            {
                std::cout << commandExecutor->executeCommand(command);
                break;
            }
            std::cout << commandExecutor->executeCommand(command);
        }
    }

    ~BankSoftware() {
        delete commandExecutor;
    }
};

int main()
{
    BankSoftware bankSoftware;
    bankSoftware.run();
}
