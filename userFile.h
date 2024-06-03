#ifndef USERFILE_H
#define USERFILE_H

#include <iostream>
#include <vector>
#include "Markup.h"
#include "File.h"
#include "user.h"
using namespace std;

class UserFile :public File
{
    CMarkup xml;
public:
    UserFile (string userFileName) : File(userFileName){
        loadUsersFromFile();
    }
    vector <User> loadUsersFromFile();
    bool addUserToFile (User &user);
    bool changePasswordInFile(int id, const string &password);
};

#endif
