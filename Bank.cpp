#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>

using std::cin;
using std::cout;
using std::ios;
using std::endl;
using std::stof;
using std::getline;
using std::string;
using std::runtime_error;
using std::exception;
using std::remove;
using std::rename;
using std::stoll;
using std::ofstream;
using std::ifstream;
using std::stringstream;

enum class MenuOption { CREATE_ACCOUNT = 1, LOGIN, QUIT };
enum class LoginOption { CHECK_BALANCE = 1, DEPOSIT, WITHDRAW, QUIT };

string FirstName, LastName, UserName, PassWord;
long long PhoneNumber;
float Amount;


inline bool check(string line, string login_username, string login_password, string fname, string lname, string usrname, string password, long long phonenumber, float amount)
{
    stringstream ss(line);

    getline(ss, FirstName, '|');
    getline(ss, LastName, '|');
    getline(ss, UserName, '|');
    getline(ss, PassWord, '|');
    string phone_str, balance_str;
    getline(ss, phone_str, '|');
    getline(ss, balance_str);

    try
    {
        PhoneNumber = stoll(phone_str);
        Amount = stof(balance_str);
    }
    catch (exception& e)
    {
        cout << "Error converting string to number: " << e.what() << endl;
        return false;
    }

    float money;
    if (login_username == UserName && login_password == PassWord)
    {
        LoginOption login_input;
        do
        {
            cout << "1.Check Balance" << "\n" << "2.Deposit" << "\n" << "3.WithDrawal" << "\n" << "4.Quit" << endl;
            int temp;
            cin >> temp;

            login_input = static_cast < LoginOption > (temp);

            switch(login_input)
            {
                case LoginOption::CHECK_BALANCE:
                    cout << "Balance is: " << Amount << endl;
                    break;
                case LoginOption::DEPOSIT:
                    try
                    {
                        int DepositAmount;
                        cout << "Enter the Deposit Amount: ";
                        cin >> DepositAmount;

                        if(DepositAmount >= 0)
                        Amount += DepositAmount;
                        else
                        throw runtime_error("Amount can't be Negative!");
                    }
                    catch(const exception& e)
                    {
                        cout << e.what() << endl;
                    }
                    break;
                case LoginOption::WITHDRAW:
                    try
                    {
                        int WithDrawAmount;
                        cout << "Enter Withdrawal Amount: ";
                        cin >> WithDrawAmount;

                        if(WithDrawAmount < 0 || WithDrawAmount >Amount)
                        {
                            throw runtime_error ("Funds Insufficient!");
                        }
                        else
                        {
                            Amount -= WithDrawAmount;
                        }
                    }
                    catch(const exception& e)
                    {
                        cout << e.what() << endl;
                    }
                    break;
                case LoginOption::QUIT:
                    cout << "See you again " << FirstName << endl;
                    break;
                default:
                    cout << "Sorry I didn't understand!" << endl; 
                    break;
            }
        }while(login_input != LoginOption::QUIT);
        return true;
    }
    return false;
}


inline void CreateAccount()
{
    ofstream UserData("User Data.txt", ios::app);

    string fname, lname, uname, pass;
    long long phonenumber;
    float amount;


    try 
    {
        if (UserData) 
        {
            cout << "Enter First name: ";
            cin.ignore();
            getline(cin, fname);

            cout << "Enter Last name: ";
            getline(cin, lname);

            cout << "Enter username: ";
            getline(cin, uname);

            cout << "Enter password: ";
            getline(cin, pass);

            cout << "Enter Phone Number: ";
            cin >> phonenumber;

            cout << "Enter Opening Balance: ";
            cin >> amount;
        }
        else
        {
            throw runtime_error("Error! in opening file, Please try again!");
        }
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

    UserData << fname << "|" << lname << "|" << uname << "|" << pass << "|" << phonenumber << "|" << amount << endl;
    UserData.close();
}


inline void Login()
{
    ifstream UserData("User Data.txt");
    ofstream temp_data("Temp Data.txt");

    try
    {
            if (UserData)
            {
                string line = "";
                string login_username, login_password;

                cout << "Enter Username: ";
                cin.ignore();
                getline(cin, login_username);

                cout << "Enter Password: ";
                getline(cin, login_password);

                string fname, lname, usrname, password;
                long long phonenumber;
                float amount;

                bool user_found = false;

                while (getline(UserData, line))
                {
                    if (check(line, login_username, login_password, fname, lname, usrname, password, phonenumber, amount))
                    {
                        user_found = true;
                        temp_data << FirstName << "|" << LastName << "|" << UserName << "|" <<
                            PassWord << "|" << PhoneNumber << "|" << Amount << endl;
                    }
                    else
                    {
                        temp_data << line << endl;
                    }
                }

                if (!user_found)
                {
                    cout << "User not found or invalid credentials!" << endl;
                }

                UserData.close();
                temp_data.close();

                remove("User Data.txt");
                rename("Temp Data.txt", "User Data.txt");
            }
        else
        {
            throw runtime_error("Error opening file 'User Data.txt' for reading. Please create an account.");
        }
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        return;
    }
}


int main()
{
    MenuOption UserInput;

    do
    {
        cout << "1.Create Account" << "\n" << "2.Login" << "\n" << "3.Quit" << endl;
        int temp;
        cin >> temp;
        UserInput = static_cast < MenuOption > (temp);

        switch(UserInput)
        {
            case MenuOption::CREATE_ACCOUNT:
                CreateAccount();
                break;
            case MenuOption::LOGIN:
                Login();
                break;
            case MenuOption::QUIT:
                exit(0);
            default:
                cout << "Sorry I didn't Understand it!" << endl;

        }
    }while(UserInput != MenuOption::QUIT);
}

