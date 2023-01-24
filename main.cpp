#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <regex>

using namespace std;

struct Node
{
    string name;
    string phone;
    Node * next;
};

class Data
{
public:
    Node * head, * tail, * manipNode, * historyStack = NULL;
    string name;
    string phone;
    bool notNull;

    Data()
    {

    }

    Data(int ident)
    {
        createList();
    }

    void createList()
    {
        head = NULL;
        cout << "\n \t Creating List..." << endl;
        Sleep(3000);
        Node * node = new Node();
        head = node;
        tail = node;
        cout << "\n \t \t List created successfully... Press any key to continue" << endl;
        system("pause>null");
    }

    void addRecord() // change to bool for verification
    {
        Node * newNode = new Node();
        newNode->name = name;
        newNode->phone = phone;

        Node * temp;
        if(head == NULL)
        {;
            createList();
        }
        temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        tail = newNode;
        cout << "\n \t Record Added Successfully!" << endl;
    }

    void searchRecord()
    {
        bool isFound = false;
        if(head == NULL)
        {
            cout << "\n \t List is empty. Nothing to search for." << endl;
            system("pause>null");
            return;
        }

        Node * temp = head;
        while(temp != NULL)
        {
            if(temp->name == name)
            {
                cout << endl << "\t Name \t \t \t Phone" << endl;
                cout << "\t " << temp->name << "\t \t \t " << temp->phone << endl;
                manipNode = temp;
                isFound = true;
                push(); //PUSH CURRENT TO STACK
                return;
            }
            temp = temp->next;
        }
        if(!isFound)
        {
            cout << "\n \t Record Not Found" << endl;
            manipNode = NULL;
        }
    }

    void editRecord(string newPhone, string newName)
    {
        if(manipNode == NULL)
        {
            cout << "\n \t Cannot edit a record that doesn't exist!" << endl;
            system("pause>null");
            return;
        }
        manipNode->name = newName;
        manipNode->phone = newPhone;
        cout << "Record Edited Successfully" << endl;
    }

    void deleteRecord()
    {
        if(head == NULL)
        {
            cout << "List is already empty!" << endl;
            system("pause>null");
            return;
        }
        if(manipNode == NULL)
        {
            cout << "Record not found or Unknown Delete error" << endl;
            return;
        }
        Node * temp = manipNode, * prev, * hold = head;

            prev = temp;

            if(temp->next != NULL && temp == head->next)
            {
                head->next = manipNode->next;
                delete(manipNode);
                //cout << "Deleted List Head. List does not exist anymore" << endl;
                cout << "Deleted First Node" << endl;
                return;
            }
            else if(temp->next == NULL && temp == head->next)
            {
                delete(head);
                cout << "Deleted List Head. List does not exist anymore" << endl;
                return;
            }
            else if(temp->next == NULL && temp != head->next)
            {
                while(hold != NULL)
                {
                    if(hold->next == NULL) break;
                    prev = hold;
                    hold = hold->next;
                }
                prev->next = NULL;
                tail = prev;
                delete(temp);
                cout << "Deleted List Tail." << endl;
                return;
            }
            else
            {
                while(hold != NULL)
                {
                    if(hold == manipNode)
                    {
                        prev->next = hold->next;
                        delete(hold);
                        break;
                    }
                    prev = hold;
                    hold = hold->next;
                }
                cout << "Deleted Middle Node." << endl; //BUG
                return;
            }
    }

    void push()
    {
        Node * newNode = new Node();
        newNode->name = manipNode->name;
        newNode->phone = manipNode->phone;
        newNode->next = historyStack;
        historyStack = newNode;
    }
};

class Console
{
public:

    const static int MAXNAME = 100;
    const static int MAXPHONE = 12;
    const string NAME_EXPR = ("^[A-Za-z\\s]{1,100}$"); //^[A-Z]{1,10}$
    const string PHONE_EXPR = ("^[0-9]{10,12}$"); //^[0-9]{1,8}$
    const string INPUT_EXPR = ("^[0-6]{1}$"); //^[0-9]{1,8}$

    string name;
    string phone;
    bool validName = false, validPhone = false;
    Data objIn;
    Data obj;

    Console()
    {

    }

    string prompt()
    {
        string input;
        bool valid = false;
        system("cls");
        cout << "\n Choose Function:" << endl;
        cout << "\t 0. Exit" << endl;
        cout << "\t 1. Add a Contact" << endl; //[DONE]
        cout << "\t 2. Edit a Contact" << endl; //[DONE]
        cout << "\t 3. Delete a Contact" << endl; //[DONE]
        cout << "\t 4. Search for a Contact" << endl; //[DONE]
        cout << "\t 5. Display All Contacts" << endl; //[DONE]
        cout << "\t 6. Display Recently Searched Contacts" << endl; //[DONE]
        cout << "\n Choice: ";
        getline(cin, input);
        valid = validateInput(input);
        return valid == 1 ? input : "-1";
    }

    bool validateInput(string input)
    {
        if(checkRegex(INPUT_EXPR, input)) return true;
        return false;
    }

    void getData()
    {
        obj.name = "";
        obj.phone = "";
        if(managePrompt())
        {
            obj.notNull = true;
            return;
        }
        obj.notNull = false;
        return;
    }

    bool managePrompt()
    {
        system("cls");
        this->obj.name = "";
        this->obj.phone = "";
        this->obj.notNull = false;
        promptName();
        promptPhone();
        if(validName && validPhone)
        {
            this->obj.name = name;
            this->obj.phone = phone;
            this->obj.notNull = true;
            return true;
        }
        name = "";
        phone = "";
        cout << "INCORRECT NAME OR PHONE NUMBER FORMAT. TRY AGAIN" << endl;
        return false;
    }

    string promptName()
    {
        this->obj.notNull = false;
        cout << "Enter Name : ";
        getline(cin, name);
        validName = validateName();
        if(validName) this->obj.notNull = true;
        return validName == 1 ? name : "";
    }

    string promptPhone()
    {
        this->obj.notNull = false;
        cout << "Enter Phone : ";
        getline(cin, phone);
        validPhone = validatePhone();
        if(validPhone) this->obj.notNull = true;
        return validPhone == 1 ? phone : "";
    }

    bool validateName()
    {
        bool check = checkRegex(NAME_EXPR, name);
        return checkRegex(NAME_EXPR, name) ? true : false;
    }

    bool validatePhone()
    {
        return checkRegex(PHONE_EXPR, phone) ? true : false;
    }

    bool checkRegex(string expr, string testString)
    {
        regex ex(expr);
        if(regex_match(testString, ex))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void printContacts(Data obj)
    {
        if(obj.head == NULL)
        {
            cout << "List is empty." << endl;
            system("pause>null");
            return;
        }

        Node * temp = obj.head->next;
        while(temp != NULL)
        {
            cout << endl << "\t Name \t \t \t Phone" << endl;
            cout << "\t " << temp->name << "\t \t \t " << temp->phone << endl;
            temp = temp->next;
        }
    }

    void printRecent(Data obj)
    {
        if(obj.historyStack == NULL)
        {
            cout << "Search History is Empty" << endl;
            return;
        }
        Node * temp = obj.historyStack;
        while(temp != NULL)
        {
            cout << "Name: " << temp->name << "\t Phone: " << temp->phone << endl;
            temp = temp->next;
        }
    }


};

int main()
{
    Data data(1);
    Console console;
    bool flow = true;
    string input;
    while(flow)
    {
        input = console.prompt();
        switch((stoi(input)))
        {
        case -1:
            {
                cout << "\n \t Wrong input, try again." << endl;
                system("pause>null");
                flow = true;
                break;
            }
        case 0:
            {
                exit(0);
            }
        case 1:
            {
                console.getData();
                if(console.obj.notNull == true)
                {
                    data.name = console.name;
                    data.phone = console.phone;
                    data.addRecord();
                }
                else if(console.obj.notNull == false)
                {
                    system("pause>null");
                    break;
                }
                system("pause>null");
                flow = true;
                break;
            }
        case 2:
            {
                data.name = console.promptName();
                data.searchRecord();
                if(data.manipNode == NULL)
                {
                    cout << "Edit Error: Record does not exist!" << endl;
                    flow = true;
                    break;
                }
                cout << "\n \t ----- New Data -----" << endl;
                data.editRecord(console.promptPhone(), console.promptName());
                system("pause>null");
                flow = true;
                break;
            }
        case 3:
            {
                data.name = console.promptName();
                data.searchRecord();
                data.deleteRecord();
                system("pause>null");
                flow = true;
                break;
            }
        case 4:
            {
                data.name = console.promptName();
                data.searchRecord();
                system("pause>null");
                flow = true;
                break;
            }
        case 5:
            {
                console.printContacts(data);
                system("pause>null");
                flow = true;
                break;
            }
        case 6:
            {
                console.printRecent(data);
                system("pause>null");
                flow = true;
                break;
            }
        }
    }
    return 0;
}




































/*
class Console
{
    const static int MAXN = 100;
    const static int MAXP = 12;

private:
    char * tempName;
    char * tempPhone;
    int size;
public:

    bool managePrompt()
    {
        bool validN = false, checkpoint = false;
        system("cls");
        //tempName = (char*)calloc(MAXN, sizeof(char));
        //if(tempName != NULL)
        //{
            checkpoint = promptName();
        //}
        //if(!checkpoint)
        //{
            validN = validateName();
        //}
        //if(validN)
        //{
            //fixInput();
            return true;
        //}
        return false;
    }

    bool promptName()
    {
        char * temp;
        temp = (char*)calloc(MAXN, sizeof(char));
        this->tempName = (char*)calloc(MAXN, sizeof(char));
        int sized = sizeof(temp);
        cout << "Size of temp : " << sized << endl;
        cout << endl << "\t \t Name (without space): ";
        cin.get(temp, MAXN, '\r\n');
        int count = 0;
        while(*(temp) != NULL)
        {
            cout << "temp = " << *(temp) << endl;
            temp++;
            count++;
        }
        cout << "Count : " << count << endl;
        size = count;
        this->tempName = (char*)realloc(this->tempName, size * sizeof(char));
        /*for(int i = 0; i <= size; i++)
        {
            this->tempName[i] = temp[i];
            cout << "tempName[i] = " << tempName[i] << endl;
        }*/
        //string tempString = temp;
        //const int length = tempString.length();
        //char * arr = new char[length + 1];
/*
        char arr[size + 1];
        strcpy(arr, temp);
        this->tempName = copyStr(arr);
        return tempName != NULL ? true : false;
    }

    char * copyStr(char arr[])
    {
        char * nChar = (char*)calloc(size, sizeof(char));
        strcpy(this->tempName, arr);
        return (char*)nChar;
    }

    bool validateName()
    {
        return this->size <= MAXN ? true : false;
    }

*/

/*
    void fixInput()
    {
        const int MAX = 100;
        int i = 0;
        for(i = 0; i < this->size; i++)
        {
            this->tempName[i] = this->str[i];
        }
        sizeN = i;
    }*/
/*
    void printall()
    {
        cout << endl;
        for(int i = 0; i < size; i++)
        {
            cout << "[" << i << "] " << tempName[i] << endl;
        }
    }

};

int main()
{
    Console console;
    if(console.managePrompt())
    {
        console.printall();
    }
    else
    {
        cout << "Invalid Name" << endl;
    }
    return 0;
}



/*Working Implementation - Does not support spaces in names


class Console
{
    const static int MAXN = 100;
    const static int MAXP = 12;

private:
    char tempName[MAXN];
    char tempPhone[MAXP];
    string str;
    string strp;
    int sizeN;
    int sizeP;

public:

    bool managePrompt()
    {
        bool validN = false;
        system("cls");
        promptName();
        validN = validateName();
        if(validN)
        {
            fixInput();
            return true;
        }
        return false;
    }

    bool promptName()
    {
        cout << endl << "\t \t Name (without space): ";
        cin >> this->str;
    }

    bool validateName()
    {
        return this->str.length() <= MAXN ? true : false;
    }

    void fixInput()
    {
        const int MAX = 100;
        int i = 0;
        for(i = 0; i < this->str.length(); i++)
        {
            this->tempName[i] = this->str[i];
        }
        sizeN = i;
    }

    void printall()
    {
        cout << endl;
        for(int i = 0; i < sizeN; i++)
        {
            cout << "[" << i << "] " << tempName[i] << endl;
        }
    }

};

int main()
{
    Console console;
    if(console.managePrompt())
    {
        console.printall();
    }
    else
    {
        cout << "Invalid Name" << endl;
    }
    return 0;
}



*/



/*


int main()
{
    Console console;
    cin.get(console.name, 100);
    int size = strlen(console.name); //sizeof
    for(int i = 0; i < size; i++)
    {
        cout << console.name[i] << " ";
    }
    system("pause>null");
    return 0;

int main()
{
    const int MAX = 100;
    char arr[MAX];
    string str;
    int count;

    cout << "Enter name: ";
    cin >> str;

    for(int i = 0; i < strlen(str) i++)
    {
        arr[i] = str[i];
        count = i;
    }

    for(int i = 0; i < count; i++)
    {
        cout << arr[i] << endl;
    }
}


*/
