#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <stdexcept>

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
using std::getline;

enum class MenuOption { CREATE_ACCOUNT = 1, LOGIN, QUIT };
enum class TypeofLogin { Tpin = 1, UserName };
enum class LoginOption { CHECK_BALANCE = 1, DEPOSIT, WITHDRAW, QUIT };

#define RunTimeError "Error Occured☹️!, Please Try again😊"
#define Message "Sorry☹️, I didn't Undestand :("
#define NegativeAmount "Sorry Mate☹️, Amount can't be Negative!😊"
#define FundsInsufficient "Sorry Mate☹️, Funds are Insufficient🥲"
#define NoUser "User not found or invalid credentials!🫡"

string FirstName, LastName, UserName, PassWord, GeneratedtPin;
long long PhoneNumber;
float Amount = 0.0;

const char Numeric[] = "1234506789";

class TpinGenerator {
public:
    TpinGenerator() {
        srand(time(0));
        cout << "Generated tpin: ";
        for (int i = 0; i < 6; i++)
            GeneratedtPin += Numeric[rand() % 9];
        cout << GeneratedtPin << endl;
    }

    string getGeneratedtPin() const {
        return GeneratedtPin;
    }

private:
    string GeneratedtPin;
};

class CreateAccount {
public:
    CreateAccount() {
        try {
            ofstream UserData("User Data.txt", ios::app);
            if (!UserData)
                throw runtime_error(RunTimeError);
            
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

            TpinGenerator o;
            cout << "You can use it at the time of Login" << endl;
            cout << "Thank you for creating an account with us, " << fname << " " << lname << "!" << endl;

            UserData << fname << "|" << lname << "|" << uname << "|" << pass << "|" << phonenumber << "|" << amount << "|" << o.getGeneratedtPin() << endl;
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
private:
    string fname, lname, uname, pass;
    long long phonenumber;
    float amount;
};

class Login {
public:
    Login() {
        try {
            ifstream UserData("User Data.txt");
            if (!UserData)
                throw runtime_error(RunTimeError);

            TypeofLogin UserInput;
            cout << "1. Tpin Login\n2. Username Login" << endl;
            int Input;
            cin >> Input;
            UserInput = static_cast<TypeofLogin>(Input);

            switch (UserInput) {
                case TypeofLogin::Tpin:
                    cout << "Enter Tpin: ";
                    cin.ignore();
                    getline(cin, login_tpin);
                    break;
                case TypeofLogin::UserName:
                    cout << "Enter Username: ";
                    cin.ignore();
                    getline(cin, login_username);
                    cout << "Enter Password: ";
                    getline(cin, login_password);
                    break;
                default:
                    throw runtime_error(Message);
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
            return;
        }
    }
    string getUsername() const { return login_username; }
    string getPassword() const { return login_password; }
    string getTpin() const { return login_tpin; }
private:
    string login_username, login_password, login_tpin;
};

class Transaction {
public:
    Transaction(float& amount) : amount(amount) {}

    void checkBalance() const {
        cout << "Balance is: " << amount << endl;
    }
private:
    float& amount;
};

class Deposit {
public:
    Deposit(float& amount) : amount(amount) {}

    void deposit() {
        try {
            int depositAmount;
            cout << "Enter the Deposit Amount: ";
            cin >> depositAmount;

            if (depositAmount >= 0)
                amount += depositAmount;
            else
                throw runtime_error("Negative amount");
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }

private:
    float& amount;
};

class Withdraw {
public:
    Withdraw(float& amount) : amount(amount) {}

    void withdraw() {
        try {
            int withdrawAmount;
            cout << "Enter Withdrawal Amount: ";
            cin >> withdrawAmount;

            if (withdrawAmount < 0 || withdrawAmount > amount) {
                throw runtime_error("Funds insufficient");
            } else {
                amount -= withdrawAmount;
            }
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }

private:
    float& amount;
};

class Checker : public virtual Login {
public:
    bool check(const string &line, const string &login_username, const string &login_password, const string &login_tpin)
    {
        stringstream ss(line);
        
        
        getline(ss, FirstName, '|');
        getline(ss, LastName, '|');
        getline(ss, UserName, '|');
        getline(ss, PassWord, '|');
        string phone_str, balance_str;
        getline(ss, phone_str, '|');
        getline(ss, balance_str, '|');
        getline(ss, GeneratedtPin, '|');

        try
        {
            PhoneNumber = stoll(phone_str);
            Amount = stof(balance_str);
        }
        catch (exception &e)
        {
            cout << e.what() << endl;
            return false;
        }

        if ((login_username == UserName && login_password == PassWord) || (login_tpin == GeneratedtPin))
        {
            cout << "User found: " << FirstName << " " << LastName << endl;

            Transaction transaction(Amount);
            Deposit deposit(Amount);
            Withdraw withdraw(Amount);
            LoginOption login_input;
            do {
                cout << "1. Check Balance\n2. Deposit\n3. Withdraw\n4. Quit" << endl;
                int temp;
                cin >> temp;
                login_input = static_cast<LoginOption>(temp);

                switch (login_input) {
                    case LoginOption::CHECK_BALANCE:
                        transaction.checkBalance();
                        break;
                    case LoginOption::DEPOSIT:
                        deposit.deposit();
                        break;
                    case LoginOption::WITHDRAW:
                        withdraw.withdraw();
                        break;
                    case LoginOption::QUIT:
                        cout << "See you again " << FirstName << endl;
                        break;
                    default:
                        cout << Message << endl;
                        break;
                }
            } while (login_input != LoginOption::QUIT);

            return true;
        }

        return false;
    }
};

class Checking : public Checker {
public:
    void CompareData() {
        ifstream UserData("User Data.txt");
        ofstream temp_data("Temp Data.txt");
        if (!UserData || !temp_data) {
            cout << RunTimeError << endl;
            return;
        }

        string line;
        bool user_found = false;
        while (getline(UserData, line)) {
            if (check(line, getUsername(), getPassword(), getTpin())) {
                user_found = true;
                temp_data << FirstName << "|" << LastName << "|" << UserName << "|" << PassWord << "|" << PhoneNumber << "|" << Amount << "|" << GeneratedtPin << endl;
            }
            else {
                temp_data << line << endl;
            }
        }

        if (!user_found) {
            cout << NoUser << endl;
        }

        UserData.close();
        temp_data.close();

        remove("User Data.txt");
        rename("Temp Data.txt", "User Data.txt");
    }
};

int main() {
    MenuOption UserInput;

    do {

            cout << "Hola Soy Sujan!👋" <<endl;
            cout << "Welcome 🙏 to Laptop Bank🏦" << endl;

            cout << "1.Create Account\n2.Login\n3.Quit" << endl;
            int temp;
            cin >> temp;
            UserInput = static_cast<MenuOption>(temp);

            switch (UserInput) {
                case MenuOption::CREATE_ACCOUNT:
                    CreateAccount();
                    break;
                case MenuOption::LOGIN:
                    Checking().CompareData();
                    break;
                case MenuOption::QUIT:
                    exit(0);
                default:
                    cout << Message << endl;
            }
    } while (UserInput != MenuOption::QUIT);

    return 0;
}


/*
        <<Updates>>
        1.Used Oops concepts
        2.More Easy to use
        3.More Compact

        <<Next Updates>>
        1.Solid Principles
        2.More Compact.


        Hecho con ❤️ por Sujan.
        tenga un  lindo día.😊❤️


*/
