#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;

// Maximum amounts constants
#define MAX_NAME_LENGTH 20
#define MAX_PASS_LENGTH 20
#define MAX_AMOUNT_DEPOSIT_WITHDRAW 2147483647	// Max range for a floating-point value
#define MAX_AMOUNT_ACCOUNT 2147483647			// Max range for a floating-point value
#define MAX_AMOUNT_PAY 2147483647				// Max range for a floating-point value

// Program control constants
#define RESTART "***RESTART***"
#define EXIT "***EXIT***"

// Data file access control constants
#define DATA_CUSTOMER "customers.txt"
#define DATA_CHECKING "checking.txt"
#define DATA_SAVINGS "savings.txt"
#define DATA_EMPLOYEE "employees.txt"
#define DATA_PAYROLL "payroll.txt"
#define DATA_MANAGER "managers.txt"

/* STRUCTURE: prompts
 * DESCRIPTION: Stores all of the prompts to be displayed to the user
 */
struct prompts {
	// Menu prompts
	string menu_main = "Enter 1 to Log in as a Customer\nEnter 2 to Log in as an Employee\nEnter 3 to Log in as a Manager\nEnter 4 to Request New Customer Account\nEnter 5 to Exit Menu";
	string menu_account = "Enter 1 to Add Funds\nEnter 2 to Withdraw Funds\nEnter 3 to Return to Exit Menu";
	string menu_customer = "Enter 1 to Manage Checking Account\nEnter 2 to Manage Savings Account\nEnter 3 to Exit Menu";
	string menu_employee = "Enter 1 to Manage a Customer Account\nEnter 2 to View Payroll Information\nEnter 3 to Add Customer Account\nEnter 4 to Remove Customer Account\nEnter 5 to View All Customer Accounts\nEnter 6 to Exit Menu";
	string menu_manager = "Enter 1 to Manage Customers\nEnter 2 to Manage Employees\nEnter 3 to Exit Menu";
	string menu_manage_customer = "Enter 1 to Add Funds to Savings\nEnter 2 to Add Funds to Checking\nEnter 3 to Withdraw From Savings\nEnter 4 to Withdraw from Checking\nEnter 5 to Exit Menu";
	string menu_customer_account_name = "Which Customer Account Would you Like to Manage?\n(Enter 'exit' to Exit Menu)";
	string menu_addRemove = "Enter 1 to Add Funds to Savings\nEnter 2 to Add Funds to Checking\nEnter 3 to Withdraw from Savings\nEnter 4 to Withdraw from Checking\nEnter 5 to Exit";
	string menu_manageEmployees = "Enter 1 to Change an Employee's Pay\nEnter 2 to Add an Employee\nEnter 3 to Remove an Employee\nEnter 4 to View All Employees\nEnter 5 to Exit Menu";
	string menu_manageCustomers = "Enter 1 to Manage a Customer Account\nEnter 2 to Add a New Customer\nEnter 3 to Remove a Customer\nEnter 4 to View all Accounts";
	string menu_andrew = "Enter 1 to manage checking\nEnter 2 to manage savings\nEnter 3 to exit";

	// Login messages
	string username = "Enter Your Username (Enter 'exit' to return to previous menu): ";
	string password = "Enter Your Password: ";
	string deposit = "Enter Amount You Would Like to Deposit";
	string withdraw = "Enter Amount You Would Like to Withdraw";

	// Information messages
	string info_balance = "Your Balance is: \n$";
	string info_hourly_rate = "Your Hourly Rate is: \n$";

	// Misc
	string viewAllAccounts = "Names\tSavings\tChecking\n------------------------------------\n";
	string hello_isItMeYourLookingFor = "Hello ";

	// Employee
	string employee_name = "Enter name of employee: ";

	// Error handling messages (Soft Errors)
	string soft_input = "Invalid Input";
	string soft_customer_name = "There is Already a Customer with that Name";
	string soft_invalid_customer = "Not a Valid Customer";
	string soft_invalid_employee = "Not a Valid Employee";
	string soft_repeat_customer = "There is already a customer by that name";
	string soft_repeat_employee = "There is already an employee by that name";
	string try_again = "Would you like to try again? (yes) -or- (no): ";
	string try_again_please = "Please Try Again";
	string exit = "Enter 'exit' to Exit Current Menu";

	// New customer data acquisition
	string new_customer_name = "Enter Name of New Customer: ";
	string new_customer_password = "Enter Password of New Customer: ";
	string new_customer_checking = "Enter Checking Balance for New Customer: ";
	string new_customer_savings = "Enter Savings Balance for New Customer: ";

	// Customer Options
	string customer_name = "Enter Name of Customer (Enter 'exit' to return to previous menu): ";

	// Manager Options
	string manager_customer = "Enter Name of Customer Account you would like to Manage (Enter 'exit' to return to previous menu): ";
	string manager_employee = "Enter Name of Employee you would like to Manage (Enter 'exit' to return to previous menu): ";
	string manager_employeePay = "Enter new pay for employee";
	string manager_currentPay = "Current pay is: $";
	string manager_newPay = "Enter new pay rate";
	string manager_newPayis = "New pay is: $";

	// Error messages
	string error_general = "ERROR: General Error";
	string error_fileAccess = "ERROR: Unable to open file";
	string error_input = "ERROR: Invalid Input";
	string error_characterOverflow = "ERROR: Too many characters";
}prompt;

/* CLASS: Input
 * DESCRIPTION: Used to obtain valid input from the user.
 */
class Input {
	private:
	public:
		Input() {};
		~Input() {};
		string get_string(int maxLength);
		string get_string(int maxLength, string prompt);
		int get_integer(int min, int max);
		int get_integer(int min, int max, string prompt);
		float get_float(float min, float max);
		float get_float(float min, float max, string prompt);

}userInput; // END CLASS Input

/* CLASS: Input
 * METHOD: getString
 * DESCRIPTION: Gets valid string from user with a number of characters less than <maxLength>.
 *				If error has occurred:
 *					Returns "false" to repeat process/prompt which called this method.
 *					Returns "exit" to end process/prompt which called this method.
 */
string Input::get_string(int maxLength) {
	string raw;
	cout << "\n--> ";

	try {
		getline(cin,raw);
		if( raw.size() > maxLength )
			throw length_error( prompt.error_characterOverflow );
		if( raw == "exit" )
			return EXIT;
	} catch (length_error x) {
		string cont;

		cout << endl << x.what();
		cout << endl << prompt.try_again;

		cont = get_string(maxLength);

		if( cont == "yes" ) {
			return RESTART;
		} else {
			return EXIT;
		} // END if...else
	} catch(...) {
		string cont;

		cout << prompt.error_input;
		cout << endl << prompt.try_again;

		cont = get_string(maxLength);

		if( cont == "yes" ) {
			return RESTART;
		} else {
			return EXIT;
		}
	}// END try...catch

	return raw;
} // END METHOD getString

/* CLASS: Input
 * METHOD: get_string (overload)
 * DESCRIPTION: Gets valid string from user, repeats prompt which calls for the user input automatically.
 */
string Input::get_string(int maxLength, string prompt) {
	string raw;

	try {
		cout << endl << prompt;
		raw = get_string(maxLength);
		if( raw == RESTART ) {
			raw = get_string(maxLength, prompt);
		}
	} catch (...) {
		cout << "ERROR: General";
	} // END try...catch

	return raw;
} // END METHOD get_string

/* CLASS: Input
 * METHOD: get_integer
 * DESCRIPTION: Gets a valid integer value from the user within the range <min> to <max>
 				Returns -1 if invalid input
 */
int Input::get_integer(int min, int max) {
	string raw;
	int newValue;
	cout << "\n--> ";

	try {
		getline(cin,raw);
		try {
			newValue = stoi(raw);
		} catch (...) {
			cout << prompt.error_input << endl;
		}
		if(newValue > max)
			throw out_of_range("Input is above acceptable value");
		if(newValue < min)
			throw out_of_range("Input is below acceptable value");
	} catch (out_of_range x) {
		string cont;

		cout << endl << x.what();
		cout << endl << prompt.try_again;

		cont = get_string(3);

		if( cont == "yes" ) {
			throw invalid_argument(RESTART);
		} else {
			throw domain_error(EXIT);
		} // END if...else
	} catch(...) {
		string cont;

		cout << prompt.soft_input;
		cout << endl << prompt.try_again;

		cont = get_string(3);

		if( cont == "yes" ) {
			newValue = get_integer(min, max);
		} else {
			throw domain_error(EXIT);
		}
	}// END try...catch

	return newValue;
} // END METHOD getInteger

/* CLASS: Input
 * METHOD: get_int (overload)
 * DESCRIPTION: Gets valid integer from user, repeats prompt which calls for the user input automatically.
 */
int Input::get_integer(int min, int max, string prompt) {
	int raw;

	try {
		cout << endl << prompt;
		raw = get_integer(min, max);
	} catch (domain_error x) {
		cout << x.what();
	} catch (invalid_argument x) {
		raw = get_integer(min, max, prompt);
	} catch (...) {

		cout << "ERROR: General";
	} // END try...catch

	return raw;
} // END METHOD get_integer

/* CLASS: Input
 * METHOD: get_float
 * DESCRIPTION: Gets a valid float value from the user within the range <min> to <max>
 				Returns -1 if invalid input
 */
float Input::get_float(float min, float max) {
	string raw;
	float newValue;
	cout << "\n--> ";

	try {
		getline(cin,raw);
		try {
			newValue = stof(raw);
		} catch (...) {
			cout << prompt.error_input << endl;
			throw invalid_argument(RESTART);
		}
		if(newValue > max)
			throw out_of_range("Input is above acceptable value");
		if(newValue < min)
			throw out_of_range("Input is below acceptable value");
	} catch (out_of_range x) {
		string cont;

		cout << endl << x.what();
		cout << endl << prompt.try_again;

		cont = get_string(3);

		if( cont == "yes" ) {
			throw invalid_argument(RESTART);
		} else {
			throw domain_error(EXIT);
		} // END if...else
	} catch(...) {
		string cont;

		cout << prompt.soft_input;
		cout << endl << prompt.try_again;

		cont = get_string(3);

		if( cont == "yes" ) {
			throw invalid_argument(RESTART);
		} else {
			throw domain_error(EXIT);
		}
	}// END try...catch

	return newValue;
} // END METHOD get_float

/* CLASS: Input
 * METHOD: get_float (overload)
 * DESCRIPTION: Gets valid float from user, repeats prompt which calls for the user input automatically.
 */
float Input::get_float(float min, float max, string prompt) {
	float raw;

	try {
		cout << endl << prompt;
		raw = get_float(min, max);
	} catch (domain_error x) {
		cout << x.what();
	} catch (invalid_argument x) {
		raw = get_float(min, max, prompt);
	} catch (...) {
		cout << "ERROR: General";
	} // END try...catch

	return raw;
} // END METHOD get_float

/* CLASS: ACCOUNT
 * DESCRIPTION: Is the base class which contains the names an accounts of every account
 */
class Account{
private:

protected:
	vector<string> names;
	vector<double> balance;
	int choice = 0;
	int length = 0;
	double amount = 0;
	int x = 0;
	int y = 0;

public:
	void ViewBalance(int);
	Account(string, string);
}; // END CLASS Account

/* CLASS: ACCOUNTS
 * DESCRIPTION: Default constructor of the class Account
                Loads and initializes every account, given the  file name
 */
Account::Account(string file_name, string username){
	int length = 0;
	int x = 0;
	int y = 0;
	string a;
	double b;
	fstream fptr;
	fptr.open(file_name);
	if(!fptr.is_open()){
		cout << prompt.error_fileAccess << endl;
	}

	fptr >> length;
	for(x=0;x<length;x++){

		fptr >> a;
		names.push_back(a);
		fptr >> b;
		balance.push_back(b);
	}

	for(x=0;x<length;x++){
		if(names[x] == username){
			cout << prompt.hello_isItMeYourLookingFor << username << endl;
			cout << prompt.info_balance << balance[x] << endl;
			y = x;
			cout << endl;
		}
	}

	fptr.close();
	double amount;
	choice = userInput.get_integer(1, 3, prompt.menu_account);
}

/* PARENT: Account
 * CLASS: SavingsAccount
 * DESCRIPTION: Derived from class Account
                Offers functionality specific to savings accounts
 */
class SavingsAccount:Account{
private:

protected:

public:
	SavingsAccount(string, string);

}; // END CLASS SavingsAccount

/* PARENT: Account
 * CLASS: SavingsAccount
 * DESCRIPTION: Defaults constructor of derived class SavingsAccount
                Deposits or withdraws funds from savings account, depending on given choice.
 */
SavingsAccount::SavingsAccount(string file_name, string username):Account(file_name, username){
	fstream fptr;
	if(choice == 1){
		// Get amount to deposit into savings account
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.deposit);
		balance[y] = balance[y] + amount;
		cout << prompt.info_balance << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}

	}
	if(choice == 2){
		// Get amount to withdraw from savings account
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.withdraw);
		balance[y] = balance[y] - amount;
		if(balance[y] < 0){
			cout << "Warning" << endl;
		}
		cout << prompt.info_balance << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}
	}
} // END CONSTRUCTOR SavingsAccount

/* PARENT: ACCOUNT
 * CLASS: CheckingAccount
 * DESCRIPTION: Stores and operates on checking accounts in the program
 */
class CheckingAccount:Account{
private:

protected:

public:
	CheckingAccount(string, string);

};

/* PARENT: Account
 * CLASS: CheckingAccount
 * DESCRIPTION: Default constructor
                Deposits or withdraws funds from the checking account
 */
CheckingAccount::CheckingAccount(string file_name, string username):Account(file_name, username){
	fstream fptr;
	if(choice == 1){
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.deposit);
		balance[y] = balance[y] + amount;
		cout << prompt.info_balance << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}

	}
	if(choice == 2){
		amount = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.withdraw);
		balance[y] = balance[y] - amount;
		if(balance[y] < 0){
			cout << "Warning" << endl;
		}
		cout << prompt.info_balance << balance[y] << endl;
		fptr.open(file_name);
		if(!fptr.is_open()){
				cout << prompt.error_fileAccess << endl;
		}
		fptr << length << endl;
		for(x=0;x<length;x++){
			fptr << names[x] << " " << balance[x] << endl;
		}
	}
} // END CONSTRUCTOR CheckingAccount

/* CLASS: Customer
 * DESCRIPTION: Stores data and functionality which correlate to customers
 */
class Customer{
private:
	int choice_c = 0;
	string username;
	string password;
	int length = 0;
	vector<string> names;
	vector<string> passwords;

public:
	Customer() {};
	int Customer_login();
	string get_username() {return username;}

}; // END CLASS Customer

/* CLASS: Customer
 * METHOD: Customer_login
 * DESCRIPTION: Accesses and stores customer data from data file
                Allows user to login as a customer
 */
int Customer::Customer_login(){
	int x = 0;
	int y = 0;
	string a;
	string b;
	int loop = 0;

	fstream fptr;
	fptr.open(DATA_CUSTOMER);
	if(!fptr.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr >> length;
	for(x=0;x<length;x++){
		fptr >> a;
		names.push_back(a);
		fptr >> b;
		passwords.push_back(b);
	}
	fptr.close();
	while(loop == 0){
		username = userInput.get_string(MAX_NAME_LENGTH, prompt.username);
		if(username == EXIT){
			return 1;
		}
		password = userInput.get_string(MAX_PASS_LENGTH, prompt.password);

	for(x=0;x<length;x++){
		if(names[x] == username && passwords[x] == password){
			cout << endl;
			cout << prompt.hello_isItMeYourLookingFor << username << endl;
			loop = 1;
			break;
		}
	}
	if(x == length){
		cout << prompt.try_again_please << endl;
			continue;
	}
	}
	return 0;

}

/* CLASS: Employee
 * DESCRIPTION: Stores data and functionality used by employees in the program
 */
class Employee{
private:
	int choice_e = 0;
	string username;
	string password;
	int length_c = 0;
	int length_e = 0;
	vector<string> names;
	vector<string> passwords;
	vector<double> payroll;
	vector<string> customer_names;
	vector<double> savings;
	vector<double> checking;
	vector<string> customer_passwords;

public:
	Employee() {};
	int Employee_Menu();
	int Employee_login();
	int Manage_Customer(string customer_name);
	int View_payroll();
	void View_All_Accounts();
	void Initialize();
	void Add_Customer();
	void Remove_Customer();
};

/* CLASS: Employee
 * METHOD: Remove_Customer
 * DESCRIPTION: Removes a customer from the record
 */
void Employee::Remove_Customer(){

	int x = 0;
	int y = 0;
	int temp;
	int loop = 0;
	string customer;

	while(loop == 0){
		customer = userInput.get_string(MAX_NAME_LENGTH, prompt.customer_name);
		for(x=0;x<length_c;x++){
			if(customer_names[x] == customer){
				loop = 1;
				y = x;
				break;
			}

		}
		if(x == length_c){
			cout << prompt.soft_invalid_customer << endl;

		}
	}

	customer_names.erase(customer_names.begin()+y);
	customer_passwords.erase(customer_passwords.begin()+y);
	savings.erase(savings.begin()+y);
	checking.erase(checking.begin()+y);
	length_c = length_c - 1;

    fstream fptr1;
	fptr1.open(DATA_CUSTOMER, fstream::out);
	if(!fptr1.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr1 << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr1 << customer_names[x] << " " << customer_passwords[x] << endl;
	}
	fptr1.close();

    fstream fptr;
	fptr.open(DATA_SAVINGS, fstream::out);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << savings[x] << endl;
	}
	fptr.close();

    fstream fptr2;
	fptr2.open(DATA_CHECKING, fstream::out);
	if(!fptr2.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr2 << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr2 << customer_names[x] << " " << checking[x] << endl;
	}
	fptr2.close();
}

/* CLASS: EMPLOYEE
 * METHOD: Add_Customer
 * DESCRIPTION: Add a customer to the customer data file
 */
void Employee::Add_Customer(){
	int x = 0;
	int loop = 0;
	string new_customer;
	string new_password;
	double new_savings;
	double new_checking;

	while(loop == 0){
		new_customer = userInput.get_string(MAX_NAME_LENGTH, prompt.new_customer_name);
		for(x=0;x<length_c;x++){
			if(customer_names[x] == new_customer){
				cout << prompt.soft_customer_name << endl;
				break;
			}
		}
		if(x == length_c){
			loop = 1;
		}
	}

	length_c = length_c + 1;

	new_password = userInput.get_string(MAX_PASS_LENGTH, prompt.new_customer_password);

	customer_names.push_back(new_customer);
	customer_passwords.push_back(new_password);

	fstream fptr;
	fptr.open(DATA_CUSTOMER);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << customer_passwords[x] << endl;
	}
	fptr.close();

	new_savings = userInput.get_float(0, MAX_AMOUNT_ACCOUNT, prompt.new_customer_savings);
	savings.push_back(new_savings);

	new_checking = userInput.get_float(0, MAX_AMOUNT_ACCOUNT, prompt.new_customer_checking);
	checking.push_back(new_checking);

	fptr.open(DATA_SAVINGS);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << savings[x] << endl;
	}
	fptr.close();

	fptr.open(DATA_CHECKING);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << checking[x] << endl;
	}
	fptr.close();

}
/* CLASS: Employee
 * METHOD: Initialize
 * DESCRIPTION: Gets every employee from the employee data file and stores them in containers to be called within the program
 */
void Employee::Initialize(){

	string a, b, e, g, h;
	int x = 0;
	double c, d, f;

	fstream fptr1;
	fptr1.open(DATA_CUSTOMER);
	if(!fptr1.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr1 >> length_c;
	for(x=0;x<length_c;x++){
		fptr1 >> a;
		customer_names.push_back(a);
		fptr1 >> b;
		customer_passwords.push_back(b);
	}
	fptr1.close();

	fstream fptr2;
	fptr2.open(DATA_SAVINGS);
	if(!fptr2.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr2 >> length_c;
	for(x=0;x<length_c;x++){
		fptr2 >> a;
		fptr2 >> c;
		savings.push_back(c);
	}
	fptr2.close();

	fstream fptr3;
	fptr3.open(DATA_CHECKING);
	if(!fptr3.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr3 >> length_c;
	for(x=0;x<length_c;x++){
		fptr3 >> a;
		fptr3 >> d;
		checking.push_back(d);
	}
	fptr3.close();

	fstream fptr4;
	fptr4.open(DATA_PAYROLL);
	if(!fptr4.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr4 >> length_e;
	for(x=0;x<length_e;x++){
		fptr4 >> e;
		names.push_back(e);
		fptr4 >> f;
		payroll.push_back(f);
	}

	fstream fptr5;
	fptr5.open(DATA_EMPLOYEE);
	if(!fptr5.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr5 >> length_e;
	for(x=0;x<length_e;x++){
		fptr5 >> g;
		names.push_back(g);
		fptr5 >> h;
		passwords.push_back(h);
	}
	fptr5.close();
}

/* CLASS: Employee
 * METHOD: View_All_Accounts
 * DESCRIPTION: Displays all of the customer accounts to the employee
 */
void Employee::View_All_Accounts(){

	int x = 0;

	prompt.viewAllAccounts;
	for(x=0;x<length_c;x++){
		cout << customer_names[x] << "\t" << savings[x] << "\t" << checking[x] << "\t" << endl;
	}
}

/* CLASS: Employee
 * METHOD: View_payroll
 * DESCRIPTION: Views the pay per hour that the employee makes
 */
int Employee::View_payroll(){
	//uses private member username
	int x = 0;

	for(x=0;x<length_e;x++){
		if(names[x] == username){
			cout << prompt.hello_isItMeYourLookingFor << username << endl;
			cout << prompt.info_hourly_rate << payroll[x] << endl;
			cout << endl;
		}
	}
	return 0;
}

/* CLASS: Employee
 * METHOD: Employee_Menu
 * DESCRIPTION: Displays menu availiable to the employee and gets user choice
 */
int Employee::Employee_Menu(){
	choice_e = userInput.get_integer(1, 6, prompt.menu_employee);
	return choice_e;
}

/* CLASS: Employee
 * METHOD: Manage_Customer
 * DESCRIPTION: Allows the employee to operate on customer accounts
 */
int Employee::Manage_Customer(string customer_name){

	int x = 0;
	int loop = 0;
	//cout << length_c << endl;

	for(x=0;x<length_c;x++){
		if(customer_names[x] == customer_name){

			cout << endl;
			loop = 1;
			return 1;
		}
	}
	if(x == length_c){
		cout << prompt.try_again_please << endl;
		return 0;
	}
	//return 2;
}

/* CLASS: Employee
 * METHOD: Employee_login
 * DESCRIPTION: Log in menu which allows the user to login and operate as an employee
 */
int Employee::Employee_login(){
	int x = 0;
	int loop = 0;

	while(loop == 0){
		username = userInput.get_string(MAX_NAME_LENGTH, prompt.username);
		if(username == EXIT){
			return 1;
		}

		password = userInput.get_string(MAX_PASS_LENGTH, prompt.password);

	for(x=0;x<length_e;x++){
		if(names[x] == username && passwords[x] == password){
			cout << endl;
			cout << prompt.hello_isItMeYourLookingFor << username << endl;
			loop = 1;
			break;
		}
	}
	if(x == 3){
		cout << prompt.try_again_please << endl;
			continue;
	}
	}
	return 0;
}

/* CLASS: Manager
 * DESCRIPTION: Stores all the functionality and data avaliable to managers
 */
class Manager{
private:
	int length_c = 0;
	int length_e = 0;
	int length_m = 0;
	int choice_m = 0;
	string username;
	string password;
	vector<string> names;
	vector<string> passwords;
	vector<double> payroll;
	vector<string> customer_names;
	vector<double> savings;
	vector<double> checking;
	vector<string> customer_passwords;
	vector<string> employee_names;
	vector<string> employee_passwords;

public:
	Manager() {};
	int manager_menu();
	int manager_login();
	void Initialize();
	int Manage_Customer(string customer_name);
	void Add_Customer();
	void Remove_Customer();
	void View_All_Accounts();
	int Manage_Employee(string employee_name);
	void Change_Pay(string employee_name);
	void Add_Employee();
	void Remove_Employee();
	void View_All_Employee();

};

/* CLASS: Manager
 * METHOD: View_All_Employee
 * DESCRIPTION: Displays the information for each employee stored in the data file
 */
void Manager::View_All_Employee(){

	int x = 0;

	cout << "Names\tPay Rate" << endl;
	for(x=0;x<length_e;x++){
		cout << employee_names[x] << "\t" << payroll[x] << endl;
	}
}

/* CLASS: Manager
 * METHOD: Remove_Employee
 * DESCRIPTION: Removes an employee from the data file
 */
void Manager::Remove_Employee(){
	int x = 0;
	int y = 0;
	int temp;
	int loop = 0;
	string employee;

	while(loop == 0){
		employee = userInput.get_string(MAX_NAME_LENGTH, prompt.employee_name);
		for(x=0;x<length_e;x++){
			if(employee_names[x] == employee){
				loop = 1;
				y = x;
				break;
			}
		}
		if(x == length_e){
			cout << prompt.soft_invalid_employee << endl;
		}
	}

	employee_names.erase(employee_names.begin()+y);
	employee_passwords.erase(employee_passwords.begin()+y);
	payroll.erase(payroll.begin()+y);
	length_e = length_e - 1;

    fstream fptr1;
	fptr1.open(DATA_EMPLOYEE, fstream::out);
	if(!fptr1.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr1 << length_e << endl;
	for(x=0;x<length_e;x++){
		fptr1 << employee_names[x] << " " << employee_passwords[x] << endl;
	}
	fptr1.close();

    fstream fptr;
	fptr.open(DATA_PAYROLL, fstream::out);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr << length_e << endl;
	for(x=0;x<length_e;x++){
		fptr << employee_names[x] << " " << payroll[x] << endl;
	}
	fptr.close();
}

/* CLASS: Manager
 * METHOD: Add_Employee
 * DESCRIPTION: Adds a new employee to the employee data file
 */
void Manager::Add_Employee(){
	string new_employee;
	string new_password;
	double new_pay;
	int loop = 0;
	int x = 0;

	while(loop == 0){
		new_employee = userInput.get_string(MAX_NAME_LENGTH, prompt.employee_name);
		for(x=0;x<length_e;x++){
			if(employee_names[x] == new_employee){
				cout << prompt.soft_repeat_employee << endl;
				break;
			}
		}
		if(x == length_e){
			loop = 1;
		}
	}

	length_e = length_e + 1;

	new_password = userInput.get_string(MAX_PASS_LENGTH, prompt.password);
	employee_passwords.push_back(new_password);

	new_pay = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.manager_employeePay);
	employee_names.push_back(new_employee);
	payroll.push_back(new_pay);

	fstream fptr;
	fptr.open(DATA_PAYROLL);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_e << endl;
	for(x=0;x<length_e;x++){
		fptr << employee_names[x] << " " << payroll[x] << endl;
	}
	fptr.close();

	fstream fptr1;
	fptr1.open(DATA_EMPLOYEE);
	if(!fptr1.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr1 << length_e << endl;
	for(x=0;x<length_e;x++){
		fptr1 << employee_names[x] << " " << employee_passwords[x] << endl;
	}
	fptr1.close();

}

/* CLASS: Manager
 * METHOD: Change_Pay
 * DESCRIPTION: Changes the pay of the selected employee
 */
void Manager::Change_Pay(string employee_name){

	int x = 0;
	int y = 0;
	fstream fptr;
	double new_pay;
	string file_name = DATA_PAYROLL;

	for(x=0;x<length_e;x++){
		if(employee_names[x] == employee_name){
			y = x;
			cout << endl;
		}
	}

			cout << prompt.manager_currentPay << payroll[y] << endl;
			new_pay = userInput.get_float(0, MAX_AMOUNT_PAY, prompt.manager_newPay);

			payroll[y] = new_pay;
			cout << prompt.manager_newPayis << payroll[y] << endl;
			fptr.open(file_name);
			if(!fptr.is_open()){
					cout << prompt.error_fileAccess << endl;
			}
			fptr << length_e << endl;
			for(x=0;x<length_e;x++){
				fptr << employee_names[x] << " " << payroll[x] << endl;
			}

			fptr.close();

}

/* CLASS: Manager
 * METHOD: Manage_Employee
 * DESCRIPTION: Manages an employee
 */
int Manager::Manage_Employee(string employee_name){

	int x = 0;
	int loop = 0;

	for(x=0;x<length_e;x++){
		if(employee_names[x] == employee_name){
			cout << endl;
			loop = 1;
			return 1;
		}
	}
	if(x == length_e){
		cout << prompt.try_again_please << endl;
		return 0;
	}
	return 2;

}

/* CLASS: Manager
 * METHOD: View_All_Accounts
 * DESCRIPTION: View all customer accounts and information
 */
void Manager::View_All_Accounts(){

	int x = 0;
	prompt.viewAllAccounts;
	for(x=0;x<length_c;x++){

		cout << customer_names[x] << "\t" << savings[x] << "\t" << checking[x] << "\t" << endl;
	}

}

/* CLASS: Manager
 * METHOD: Remove_Customer
 * DESCRIPTION: Removes customer from the customer data file
 */
void Manager::Remove_Customer(){

	int x = 0;
	int y = 0;
	int temp;
	int loop = 0;
	string customer;

	while(loop == 0){
		customer = userInput.get_string(MAX_NAME_LENGTH, prompt.customer_name);
		for(x=0;x<length_c;x++){
			if(customer_names[x] == customer){
				loop = 1;
				y = x;
				break;
			}

		}
		if(x == length_c){
			cout << prompt.soft_invalid_customer << endl;
		}
	}

	customer_names.erase(customer_names.begin()+y);
	customer_passwords.erase(customer_passwords.begin()+y);
	savings.erase(savings.begin()+y);
	checking.erase(checking.begin()+y);
	length_c = length_c - 1;

    fstream fptr1;
	fptr1.open(DATA_CUSTOMER, fstream::out);
	if(!fptr1.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr1 << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr1 << customer_names[x] << " " << customer_passwords[x] << endl;
	}
	fptr1.close();

    fstream fptr;
	fptr.open(DATA_SAVINGS, fstream::out);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << savings[x] << endl;
	}
	fptr.close();

    fstream fptr2;
	fptr2.open(DATA_CHECKING, fstream::out);
	if(!fptr2.is_open()){
			cout << prompt.error_fileAccess << endl;
	}
	fptr2 << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr2 << customer_names[x] << " " << checking[x] << endl;
	}
	fptr2.close();
}

/* CLASS: Manager
 * METHOD: Add_Customer
 * DESCRIPTION: Adds a new customer to the customer data file
 */
void Manager::Add_Customer(){
	int x = 0;
	int loop = 0;
	string new_customer;
	string new_password;
	double new_savings;
	double new_checking;

	while(loop == 0){
		new_customer = userInput.get_string(MAX_NAME_LENGTH, prompt.customer_name);
		for(x=0;x<length_c;x++){
			if(customer_names[x] == new_customer){
				cout << "there is already a customer with that name" << endl;
				break;
			}
		}
		if(x == length_c){
			loop = 1;
		}
	}

	length_c = length_c + 1;

	new_password = userInput.get_string(MAX_PASS_LENGTH, prompt.password);
	customer_names.push_back(new_customer);
	customer_passwords.push_back(new_password);

	fstream fptr;
	fptr.open(DATA_CUSTOMER);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << customer_passwords[x] << endl;
	}
	fptr.close();

	new_savings = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.new_customer_savings);
	savings.push_back(new_savings);
	new_checking = userInput.get_float(0, MAX_AMOUNT_DEPOSIT_WITHDRAW, prompt.new_customer_checking);
	checking.push_back(new_checking);

	//fstream fptr;
	fptr.open(DATA_SAVINGS);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << savings[x] << endl;
	}
	fptr.close();

	fptr.open(DATA_CHECKING);
	if(!fptr.is_open()){
			cout << prompt.error_fileAccess << endl;
	}

	fptr << length_c << endl;
	for(x=0;x<length_c;x++){
		fptr << customer_names[x] << " " << checking[x] << endl;
	}
	fptr.close();

}

/* CLASS: Manager
 * METHOD: Manage_Customer
 * DESCRIPTION: Allows the manager to manage a customer account
 */
int Manager::Manage_Customer(string customer_name){

	int x = 0;
	int loop = 0;

	for(x=0;x<length_c;x++){
		if(customer_names[x] == customer_name){
			cout <<endl;
			loop = 1;
			return 1;
		}
	}
	if(x == length_c){
		cout << prompt.try_again_please << endl;
		return 0;
	}
	return 2;
}

/* CLASS: Manager
 * METHOD: manager_login
 * DESCRIPTION: Verifies that the user is a manager as stored in the manager data file
 */
int Manager::manager_login(){

	int x = 0;
	int loop = 0;

	while(loop == 0){
		username = userInput.get_string(MAX_NAME_LENGTH, prompt.username);
		if(username == EXIT){
			return 1;
		}
		password = userInput.get_string(MAX_PASS_LENGTH, prompt.password);

	for(x=0;x<length_e;x++){
		if(names[x] == username && passwords[x] == password){
			cout << endl;
			cout << prompt.hello_isItMeYourLookingFor << username << endl;
			loop = 1;
			break;
		}
	}
	if(x == 3){
		cout << prompt.try_again_please << endl;
			continue;
	}
	}
	return 0;
}

/* CLASS: Manager
 * METHOD: Initialize
 * DESCRIPTION: Gets manager data from manager data file and prepares it to be operated on
 */
void Manager::Initialize(){

	string a, b, e, g, h, i, j;
	int x = 0;
	double c, d, f;

	fstream fptr1;
	fptr1.open(DATA_CUSTOMER);
	if(!fptr1.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr1 >> length_c;
	for(x=0;x<length_c;x++){
		fptr1 >> a;
		customer_names.push_back(a);
		fptr1 >> b;
		customer_passwords.push_back(b);
	}
	fptr1.close();

	fstream fptr2;
	fptr2.open(DATA_SAVINGS);
	if(!fptr2.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr2 >> length_c;
	for(x=0;x<length_c;x++){
		fptr2 >> a;
		fptr2 >> c;
		savings.push_back(c);
	}
	fptr2.close();

	fstream fptr3;
	fptr3.open(DATA_CHECKING);
	if(!fptr3.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr3 >> length_c;
	for(x=0;x<length_c;x++){
		fptr3 >> a;
		fptr3 >> d;
		checking.push_back(d);
	}
	fptr3.close();

	fstream fptr4;
	fptr4.open(DATA_PAYROLL);
	if(!fptr4.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr4 >> length_e;
	for(x=0;x<length_e;x++){
		fptr4 >> e;
		//names.push_back(e);
		fptr4 >> f;
		payroll.push_back(f);
	}

	fstream fptr5;
	fptr5.open(DATA_EMPLOYEE);
	if(!fptr5.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr5 >> length_e;
	for(x=0;x<length_e;x++){
		fptr5 >> g;
		employee_names.push_back(g);
		fptr5 >> h;
		employee_passwords.push_back(h);
	}
	fptr5.close();

	fstream fptr6;
	fptr6.open(DATA_MANAGER);
	if(!fptr6.is_open()){
		cout << prompt.error_fileAccess << endl;
	}
	fptr6 >> length_m;
	for(x=0;x<length_m;x++){
		fptr6 >> i;
		names.push_back(i);
		fptr6 >> j;
		passwords.push_back(j);
	}
	fptr6.close();
}

/* CLASS: Manager
 * METHOD: manager_menu
 * DESCRIPTION: Displays the functionality availiable to a manager, and gets the user input
 */
int Manager::manager_menu(){
	choice_m = userInput.get_integer(0, 3, prompt.menu_manager);
	return choice_m;
}

int menu(){
	int choice = 0;
	choice = userInput.get_integer(1, 5, prompt.menu_main);
	return choice;
}

int main(void){
	int choice;
	int choice_c;
	int choice_e;
	int return_to_main = 0;
	int thing1 = 0;
	int thing2 = 0;
	int thing3 = 0;
	int second_loop = 0;

	string c = DATA_CHECKING;
	string s = DATA_SAVINGS;

	string username;
	string customer_name;
	int x, y;
	int choice_m1;
	int choice_m2 = 1;
	int choice_m3;
	string employee_name;
	Customer customer1;
	Employee employee1;
	Manager manager1;
	int third_loop = 0;

	while(return_to_main == 0){

		choice = menu();

		switch (choice){
		case 1:	// Log in as customer
			thing1 = customer1.Customer_login();
			username = customer1.get_username();

			if(thing1 == 1){
				continue;
			}
			second_loop = 0;
			while(second_loop == 0){
				choice_c = userInput.get_integer(1, 3, prompt.menu_customer);
				if(choice_c == 1){
					CheckingAccount checking(c, username);
				} else if(choice_c == 2){
					SavingsAccount savings(s, username);
				} else if(choice_c == 3){
					second_loop = 1;
				} else {
					cout << prompt.error_general;
				}
			}
			break;

		case 2:	// Login as an employee
			employee1.Initialize();
			thing2 = employee1.Employee_login();
			if(thing2 == 1){
				continue;
			}
			second_loop = 0;
			while(second_loop == 0){
				choice_e = employee1.Employee_Menu();
				while(choice_e == 1){
					customer_name = userInput.get_string(MAX_NAME_LENGTH, prompt.manager_customer);
					if(customer_name == EXIT){
						choice_e = 0;
						continue;
					}

					x = employee1.Manage_Customer(customer_name);

					if(x == 0){
						cout << prompt.soft_invalid_customer << endl;
					}

					if(x == 1){
						int g = userInput.get_integer(0,3, prompt.menu_andrew);
						if(g == 1)
							CheckingAccount checking1(c, customer_name);
							choice_e = 0;
						if(g == 2)
							SavingsAccount savings1(s, customer_name);
							choice_e = 0;
						if(g == 3)
							choice_e = 0;
						continue;
					}
				}
				if(choice_e == 2){
					employee1.View_payroll();
				}
				if(choice_e == 3){
					employee1.Add_Customer();
				}
				if(choice_e == 4){	// Remove Customer
					employee1.Remove_Customer();
				}
				if(choice_e == 5){
					//view all accounts
					employee1.View_All_Accounts();
				}
				if(choice_e == 6){
					//exit loop
					second_loop = 1;
				}
			}

		break;

		case 3: // Log in as a manager
			manager1.Initialize();
			thing3 = manager1.manager_login();
			if(thing3 == 1){
				continue;
			}
			choice_m1 = manager1.manager_menu();

			if(choice_m1 == 1){
				//choice_m2 = userInput.get_integer(0, 4, prompt.menu_manage_customer);
				while(choice_m2 == 1){
					customer_name = userInput.get_string(MAX_NAME_LENGTH, prompt.manager_customer);
					if(customer_name == EXIT){
						choice_m2 = 0;
						continue;
					}
					x = manager1.Manage_Customer(customer_name);
					if(x == 0){
						cout << prompt.soft_invalid_customer << endl;
					}
					if(x == 1){
						int x = userInput.get_integer(0,3, prompt.menu_andrew);
						if(x == 1)
							CheckingAccount checking1(c, customer_name);
						if(x == 2)
							SavingsAccount savings1(s, customer_name);
						if(x == 3)
							choice_e = 0;
					}
				}
				if(choice_m2 == 2){
					manager1.Add_Customer();
				}
				if(choice_m2 == 3){
					//remove customer
					manager1.Remove_Customer();
				}
				if(choice_m2 == 4){
					manager1.View_All_Accounts();
				}
				if(choice_m2 == 5){
					choice_m1 = 0;
				}
			}

			while(choice_m1 == 2){
				//manage employees
				choice_m3 = userInput.get_integer(0, 5, prompt.menu_manageEmployees);
				while(choice_m3 == 1){
					employee_name = userInput.get_string(MAX_NAME_LENGTH, prompt.manager_employee);
					//cout << "1" << endl;
					if(employee_name == EXIT){
						choice_m3 = 0;
						//cout << "2" << endl;
						continue;
					}
					//cout << "3" << endl;
					y = manager1.Manage_Employee(employee_name);
					//cout << "4" << endl;
					if(y == 0){
						cout << prompt.soft_invalid_employee << endl;
					}
					if(y == 1){
						manager1.Change_Pay(employee_name);
						choice_m3 = 0;
					}
				}
				if(choice_m3 == 2){
					//add employee
					manager1.Add_Employee();
				}
				if(choice_m3 == 3){
					//remove employee
					manager1.Remove_Employee();
				}
				if(choice_m3 == 4){
					//view all
					manager1.View_All_Employee();

				}
				if(choice_m3 == 5){
					//exit
					choice_m1 = 1;
				}
			if(choice_m1 == 3){
				//loop = 1;

			}
			}


		break;
		case 4: // Add new customer
			employee1.Initialize();
			employee1.Add_Customer();
		break;
		case 5:	// Exit program
			cout << "thanks for using this random bank" << endl;
			return 3;
		break;
		default:
			cout << "incorrect input" << endl;
			return 4;

	}
	}
	return 0;
} // END FUNCTION main
