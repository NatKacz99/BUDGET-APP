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
            if (operation.id > lastId) {
                    lastId = operation.id;
                }

            xml.FindElem("userId");
            operation.userId = stoi(xml.GetData());

            xml.FindElem("date");
            operation.date = stoi(xml.GetData());

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
bool FilesOperation::addOperationToFile (Operation &operation)
{
    if(!xml.Load(getFileName())){
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Root");
    }
    xml.ResetMainPos();
    xml.FindElem("Root");
    xml.IntoElem();
    xml.AddElem("Operation");
    xml.IntoElem();
    xml.AddElem("id", to_string(operation.id));
    xml.AddElem("userId", to_string(operation.userId));
    xml.AddElem("date", operation.date);
    xml.AddElem("item", operation.item);
    string formattedAmount = CashMethods::formatAmount(operation.amount);
    xml.AddElem("amount", formattedAmount);
    xml.OutOfElem();
    xml.OutOfElem();

    if (!xml.Save(getFileName())){
        cerr << "Error: Unable to save the XML file" << endl;
        return false;
    }
    operation.id = getLastId() + 1;
    lastId = operation.id;
    return true;
}
