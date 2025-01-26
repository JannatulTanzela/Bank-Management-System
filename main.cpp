#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;
class account
{
    int acno;
    char name[50];
    int deposit;
    char type;
public:
    void create_account();
    void show_account() const;
    void dep(int);
    void draw(int);
    void report() const;
    int retacno() const;
    int retdeposit() const;
    char rettype() const;
};
void account::create_account()
{
    system("clear");
    //Handle invalid account number input
    while (true)
    {
        cout << "\n\tEnter the Account No. : ";
        cin >> acno;
        if(cin.fail() || acno <= 0)  //Check if the input is a valid positive integer
        {
            cin.clear(); //Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignore invalid input
            cout << "\n\tInvalid input. Please enter a valid account number.\n";
        }
        else
        {
            break; //Break the loop if the input is valid
        }
    }
    //Handle empty name input
    cin.ignore();  //To ignore any leftover newline character from the previous input
    cout << "\n\n\tPlease Enter the Name of the Account holder Here : ";
    while (true)
    {
        cin.getline(name, 50);
        if (strlen(name) == 0)    //Check if the name is empty
        {
            cout << "\n\tName cannot be empty. Please enter a valid name: ";
        }
        else
        {
            break;
        }
    }
    //Handle invalid account type input
    while (true)
    {
        cout << "\n\tEnter Type of the Account (C/S) : ";
        cin >> type;
        type = toupper(type); //Convert to uppercase
        if (type == 'C' || type == 'S')  // Check if the type is 'C' or 'S'
        {
            break;
        }
        else
        {
            cout << "\n\tInvalid account type. Please enter 'C' for Current or 'S' for Savings.\n";
        }
    }
    // Handle invalid deposit amount input
    while (true)
    {
        cout << "\n\tEnter The Initial amount : ";
        cin >> deposit;
        if (cin.fail() || deposit < 0)  //Check if the deposit is a valid number and positive
        {
            cin.clear(); //Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignore invalid input
            cout << "\n\tInvalid deposit amount. Please enter a valid positive amount.\n";
        }
        else
        {
            break;
        }
    }

    cout << "\n\n\tAccount Created..";
}
void account::show_account() const
{
    cout << "\n\tAccount No. : " << acno;
    cout << "\n\tAccount Holder Name : ";
    cout << name;
    cout << "\n\tType of Account : " << type;
    cout << "\n\tBalance amount : " << deposit;
}


void account::dep(int x)
{
    deposit += x;
}

void account::draw(int x)
{
    deposit -= x;
}

void account::report() const
{
    cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::retacno() const
{
    return acno;
}

int account::retdeposit() const
{
    return deposit;
}

char account::rettype() const
{
    return type;
}
void write_account();
void display_sp(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

int main()
{
    char ch;
    int num;
    do
    {
        system("CLS");
        cout << "\n\t\n";
        cout << "\t\BANK MANAGEMENT SYSTEM";
        cout << "\n\t_____________________\n";

        cout << "\n\t#MAIN MENU\n";
        cout << "\n\t1. NEW ACCOUNT";
        cout << "\n\t2. DEPOSIT AMOUNT";
        cout << "\n\t3. WITHDRAW AMOUNT";
        cout << "\n\t4. BALANCE ENQUIRY";
        cout << "\n\t5. ALL ACCOUNT HOLDER LIST";
        cout << "\n\t6. CLOSE AN ACCOUNT";
        cout << "\n\t7. EXIT";
        cout << "\n\n\tSelect Your Option (1-7): ";
        cin >> ch;
        switch (ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            system("CLS");
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            deposit_withdraw(num, 1);
            break;
        case '3':
            system("CLS");
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            deposit_withdraw(num, 2);
            break;
        case '4':
            system("CLS");
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            system("CLS");
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            delete_account(num);
            break;
        case '7':
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();
    }
    while (ch != '7');
    return 0;
}
void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.data", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
    outFile.close();
}

void display_sp(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.data", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\tBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
    {
        if (ac.retacno() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\n\tAccount number does not exist";
}


void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.data", ios::binary);
    if (!inFile)
    {
        cout << "File could not be opened! Press any Key...";
        return;
    }
    outFile.open("Temp.data", ios::binary);
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
    {
        if (ac.retacno() != n)
        {
            outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.data");
    rename("Temp.data", "account.data");
    cout << "\n\n\tAccount deleted successfully!";
}

void display_all()
{
    system("CLS");
    account ac;
    ifstream inFile;
    inFile.open("account.data", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type     Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}
void deposit_withdraw(int n, int option)
{
    account ac;
    int amt;
    bool found = false;
    fstream File;
    File.open("account.data", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be opened! Press any Key...";
        return;
    }
    while (File.read(reinterpret_cast<char*>(&ac), sizeof(account)))
    {
        if (ac.retacno() == n)
        {
            ac.show_account();
            if (option == 1)
            {
                cout << "\n\n\tEnter the amount to deposit: ";
                cin >> amt;
                ac.dep(amt);
            }
            else if (option == 2)
            {
                cout << "\n\n\tEnter the amount to withdraw: ";
                cin >> amt;
                if (ac.retdeposit() >= amt)
                {
                    ac.draw(amt);
                }
                else
                {
                    cout << "Insufficient balance!";
                    continue;
                }
            }
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(account));
            found = true;
            break;
        }
    }
    File.close();
    if (!found)
    {
        cout << "\n\n\tAccount not found!";
    }
}
