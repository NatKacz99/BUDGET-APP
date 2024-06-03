#include "filesOperation.h"

vector <Operation> FilesOperation::loadOperationsFromFile (const int loggedUserId)
{
    Operation operation;
    vector <Operation> operations;
    if(!xml.Load(getFileName())){
        cout << "File doesn't exist" << endl;
        return operations;
    }
    else{
        xml.ResetPos();
        xml.IntoElem();
        xml.FindElem();
        xml.IntoElem();
        xml.FindElem();

        do {
            xml.IntoElem();

            xml.FindElem("id");
            operation.id = stoi(xml.GetData());

            xml.FindElem("userId");
            operation.userId = stoi(xml.GetData());

            xml.FindElem("date");
            operation.date = xml.GetData();

            xml.FindElem("item");
            operation.item = xml.GetData();

            xml.FindElem("amount");
            operation.amount = stod(xml.GetData());

            if (operation.userId == loggedUserId){
              operations.push_back(operation);
            }

            xml.OutOfElem();

        } while (xml.FindElem());

    }
    return operations;
}
bool FilesOperation::addOperationToFile (const Operation &operation)
{
    if(!xml.Load(getFileName())){
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Root");
    }
    else{
        xml.ResetPos();
        xml.FindElem();
        xml.IntoElem();
        xml.AddElem("Operation");
        xml.IntoElem();
        xml.AddElem("id", to_string(operation.id));
        xml.AddElem("userId", to_string(operation.userId));
        xml.AddElem("date", operation.date);
        xml.AddElem("item", operation.item);
        xml.AddElem("amount", operation.amount);

        xml.Save(getFileName());
        xml.OutOfElem();
        cout << "You added operation right" << endl;
        return true;
    }
    return false;
}
