#include "userManager.h"

bool UserManager::checkIfLoginExists(const string &login)
{
    for(size_t i = 0; i < users.size(); i++){
        if(login == users[i].login){
            return true;
        }
    }
    return false;
}
int UserManager::getLoggedUserId()
{
    return loggedUserId;
}
User UserManager::enterUserData()
{
    User person;
    string firstPassword = "", secondPassword = "";

    cout << "Enter name: " << endl;
    person.name = AuxiliaryMethod::enterLine();
    if(!AuxiliaryMethod::validateInput(person.name)){
        cout << "Incorrect name. Try again" << endl;
        system("pause");
    }
    cout << "Enter surname: " << endl;
    person.surname = AuxiliaryMethod::enterLine();
    if(!AuxiliaryMethod::validateInput(person.surname)){
        cout << "Incorrect surname. Try again" << endl;
        system("pause");
    }
    while (true) {
        cout << "Enter login: " << endl;
        person.login = AuxiliaryMethod::enterLine();
        if (checkIfLoginExists(person.login)) {
            cout << "This login already exists. Please choose another one." << endl;
        } else {
            break;
        }
    }
    while(1){
        cout << "Enter password: " << endl;
        firstPassword = AuxiliaryMethod::enterLine();
        cout << "Repeat password: " << endl;
        secondPassword = AuxiliaryMethod::enterLine();
        if(firstPassword == secondPassword){
            person.password = secondPassword;
            break;
        }
        else{
            cout << "Entered passwords are differ. Try again" << endl;
        }
    }
    return person;
}
void UserManager::registerUser()
{
    system ("cls");
    User user = enterUserData();
    users.push_back(user);
    userFile.addUserToFile(user);
}
void UserManager::loginUser()
{
    string login = "", password = "";
    cout << "Enter login: " << endl;
    login = AuxiliaryMethod::enterLine();
    for(User user : users){
        if(checkIfLoginExists(login)){
                for (int trials = 3; trials > 0; trials--){
                    cout << "Enter your password, " << trials << " attempts left: ";
                    password = AuxiliaryMethod::enterLine();

                    if (user.password == password){
                        cout << "Logged." << endl;
                        loggedUserId = user.id;
                        return;
                    }
                }
                cout << "3 times wrong password." << endl;
                system("pause");
                return;
            }
   }
    cout << "Login doesn't exist. Try enter again" << endl;
    system("pause");
}
void UserManager::changeUserPassword()
{
    string currentPassword, newPassword;
    cout << "Enter current password: " << endl;
    currentPassword = AuxiliaryMethod::enterLine();
    for(User user : users){
        if(currentPassword == user.password){
            cout << "Enter new password: ";
            newPassword = AuxiliaryMethod::enterLine();
            user.password = newPassword;
            userFile.changePasswordInFile(user.id, user.password);
        }
        else {
            cout << "Incorrect password. Try again" << endl;
            system("pause");
        }
    }
}
void UserManager::logoutUser()
{
    loggedUserId = 0;
}
bool UserManager::isUserLoggedIn()
{
    if(getLoggedUserId() != 0){
        return true;
    }
    else return false;
}
