# BankSoftware

#### *Course project for Introduction to Programming course*   

#### The project contains some simple functionalities for bank software

## Structure

- User class - the user has username, password, balance
- CommandExecutor class -  executes the commands 
- UserDatabase class - keeps track of the users in a hashmap, has a method to read and write the users to a file
- BankSoftware class - consists of a UserDatabase and a CommandExecutor

## Functionalities
- help - displays all the commands
- Login - The user should enter his username and password
- Register - The user should enter his username, password and confirm his password
- Logout - Logs out the user
- Deposit - The user should enter the valid deposit amount
- Withdraw - The user should enter the withdraw amount and. The overdraft should be less than 10 000
- Transfer - Enter the second user's username. If the second user exists and the overdraft is less than 10 000 the transfer will be successful 
- Cancel account - Cancels the account if the balance is 0
