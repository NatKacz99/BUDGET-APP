#include "userFile.h"

vector <User> UserFile::loadUsersFromFile()
{
    vector <User> users;
    User user;
    if(!xml.Load(getFileName())){
        cout << "File doesn't exist" << endl;
        return users;
    }
    else{
        xml.ResetPos();
        xml.FindElem();
        xml.IntoElem();
        xml.FindElem();
        do{
            xml.IntoElem();

            xml.FindElem("id");
            user.id = stoi(xml.GetData());

            xml.FindElem("name");
            user.name = xml.GetData();

            xml.FindElem("surname");
            user.surname = xml.GetData();

            xml.FindElem("login");
            user.login = xml.GetData();

            xml.FindElem("password");
            user.password = xml.GetData();

            xml.OutOfElem();
        } while(xml.FindElem());
    }
    return users;
}
bool UserFile::addUserToFile (User &user)
{
    user.id = getLastId() + 1;
    if(!xml.Load(getFileName())){
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Root");
    }
    xml.ResetPos();
    xml.FindElem("Root");
    xml.IntoElem();
    xml.AddElem("User");
    xml.IntoElem();
    xml.AddElem("id", to_string(user.id));
    xml.AddElem("name", user.name);
    xml.AddElem("surname", user.surname);
    xml.AddElem("login", user.login);
    xml.AddElem("password", user.password);

    if (!xml.Save(getFileName())){
        cerr << "Error: Unable to save the XML file" << endl;
        return false;
    }
    xml.Save(getFileName());
    lastId = user.id;
    xml.OutOfElem();
    cout << "User has been added successfully" << endl;
    system("pause");
    return true;
}
bool UserFile::changePasswordInFile(int id, const string &password)
{
    if(!xml.Load(getFileName())){
        cout << "File doesn't exist" << endl;
        return false;
    }
    else{
        while (xml.FindElem("User")){
            xml.IntoElem();
            xml.FindElem("id");

            if (stoi(xml.GetData()) == id){
                xml.FindElem("password");
                xml.SetData(password);
                xml.Save(getFileName());
                cout << "Password has been changed" << endl;
                return true;
            }
        }
        xml.OutOfElem();
    }
    cout << "User with this id doesn't exist" << endl;
    return false;
}