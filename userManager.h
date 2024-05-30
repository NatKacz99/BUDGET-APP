#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "userFile.h"
#include "user.h"
#include "auxiliaryMethod.h"

using namespace std;

class UserManager
{
    int loggedUserId;
    UserFile userFile;
    vector <User> users;

    User enterUserData();

public:
    UserManager(string userFileName) : userFile(userFileName) {
        loggedUserId = 0;
        users = userFile.loadUsersFromFile();
    }
    void registerUser();
    void loginUser();
    void changeUserPassword();
    void logoutUser();
    bool isUserLoggedIn();
    int getLoggedUserId();
    bool checkIfLoginExists(const string &login);
    int increaseUserIdAfterRegisterUser();
};

#endif
