
This C++ program simulates a basic banking system with the following functionalities:

`Account Creation`
      Users can create an account by providing their first name, last name, username, password, phone number, and opening balance.
      A 6-digit TPIN (Transaction Personal Identification Number) is automatically generated for the user.
      Account information is stored in a text file named "User Data.txt".
      
`Login`
      Users can log in using either their TPIN or username/password combination.
      If the login credentials are correct, the user's information is displayed, and they are given options to check balance, deposit, withdraw, or quit.
      
`Transactions`
      Users can check their account balance, deposit funds, withdraw funds, or quit.
      Error messages are displayed for scenarios such as invalid input, file handling errors, negative amounts during transactions, and insufficient funds during withdrawals.
      
`Data Management`
      Account data is stored in a text file in the format: first name|last name|username|password|phone number|balance|TPIN.
      When a user logs in, their information is checked against the data file.
      If a user makes changes to their account (e.g., deposit or withdrawal), the data file is updated.
      
`How it works`
      Account Creation (CreateAccount class):
      Users input their details: first name, last name, username, password, phone number, and opening balance.
      A TPIN is generated automatically.
      User data is stored in "User Data.txt".
      
`Login (Login class)`
      Users can log in using their TPIN or username/password combination.
      User data is checked against "User Data.txt".
      If login is successful, the user's information is displayed, and they are prompted with options.
      
`Transactions (Transaction class)`
      Users can check balance, deposit, withdraw, or quit.
      Error handling ensures data integrity and prevents invalid transactions.
      
`Data Management (Checker and Checking classes)`
      Account data is read from "User Data.txt" and compared during login.
      If a user makes changes to their account, the data file is updated.
      
`Key Features`
      Clear and concise user interface.
      Robust error handling for user input and file operations.
      Efficient data management with file handling.
      Encapsulation to ensure data security and integrity
