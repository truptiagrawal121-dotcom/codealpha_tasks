#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string details;

    Transaction(string t, double a, string d)
        : type(t), amount(a), details(d) {}
};

class Account {
public:
    int accountNumber;
    double balance;
    vector<Transaction> history;

    Account(int number, double initialBalance = 0.0)
        : accountNumber(number), balance(initialBalance) {}

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount.\n";
            return;
        }

        balance += amount;
        history.emplace_back("Deposit", amount, "Cash deposited");
        cout << "Deposit successful!\n";
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount.\n";
            return false;
        }

        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }

        balance -= amount;
        history.emplace_back("Withdrawal", amount, "Cash withdrawn");
        cout << "Withdrawal successful!\n";
        return true;
    }

    void showBalance() const {
        cout << "Account Number: " << accountNumber << '\n';
        cout << "Available Balance: Rs. "
             << balance << '\n';
    }

    void showTransactions() const {
        if (history.empty()) {
            cout << "No transactions available.\n";
            return;
        }

        cout << "\n--- Transaction History ---\n";

        for (int i = static_cast<int>(history.size()) - 1;
             i >= 0; i--) {
            cout << history[i].type
                 << " | Rs. " << history[i].amount
                 << " | " << history[i].details << '\n';
        }
    }
};

class Customer {
public:
    int customerId;
    string name;
    string phone;
    vector<Account> accounts;

    Customer(int id, string n, string p)
        : customerId(id), name(n), phone(p) {}

    void createAccount(int accountNumber, double initialBalance) {
        if (initialBalance < 0) {
            cout << "Initial balance cannot be negative.\n";
            return;
        }

        for (int i = 0; i < static_cast<int>(accounts.size()); i++) {
            if (accounts[i].accountNumber == accountNumber) {
                cout << "Account already exists for this customer.\n";
                return;
            }
        }

        accounts.emplace_back(accountNumber, initialBalance);
        cout << "Account created successfully!\n";
    }

    Account* findAccount(int accountNumber) {
        for (int i = 0; i < static_cast<int>(accounts.size()); i++) {
            if (accounts[i].accountNumber == accountNumber) {
                return &accounts[i];
            }
        }

        return nullptr;
    }

    void displayCustomer() const {
        cout << "\nCustomer ID: " << customerId
             << "\nName: " << name
             << "\nPhone: " << phone << '\n';
    }
};

class BankingSystem {
private:
    vector<Customer> customers;
    int nextCustomerId = 1;
    int nextAccountNumber = 1001;

public:
    Customer* findCustomer(int customerId) {
        for (int i = 0; i < static_cast<int>(customers.size()); i++) {
            if (customers[i].customerId == customerId) {
                return &customers[i];
            }
        }

        return nullptr;
    }

    Account* findAccount(int accountNumber) {
        for (int i = 0; i < static_cast<int>(customers.size()); i++) {
            Account* account = customers[i].findAccount(accountNumber);
            if (account != nullptr) {
                return account;
            }
        }

        return nullptr;
    }

    void createCustomer() {
        string name, phone;

        cout << "Enter customer name: ";
        getline(cin >> ws, name);

        cout << "Enter phone number: ";
        getline(cin >> ws, phone);

        customers.emplace_back(nextCustomerId, name, phone);

        cout << "Customer created successfully!\n";
        cout << "Customer ID: " << nextCustomerId << '\n';
        nextCustomerId++;
    }

    void createAccount() {
        int customerId;
        double initialBalance;

        cout << "Enter customer ID: ";
        if (!(cin >> customerId)) {
            invalidInput();
            return;
        }

        Customer* customer = findCustomer(customerId);

        if (customer == nullptr) {
            cout << "Customer not found.\n";
            return;
        }

        cout << "Enter initial deposit: Rs. ";
        if (!(cin >> initialBalance)) {
            invalidInput();
            return;
        }

        if (initialBalance < 0) {
            cout << "Initial balance cannot be negative.\n";
            return;
        }

        customer->createAccount(nextAccountNumber, initialBalance);

        Account* account = customer->findAccount(nextAccountNumber);

        if (account != nullptr) {
            if (initialBalance > 0) {
                account->history.emplace_back(
                    "Deposit", initialBalance, "Initial deposit");
            }

            cout << "Account Number: " << nextAccountNumber << '\n';
            nextAccountNumber++;
        }
    }

    void depositMoney() {
        int number;
        double amount;

        cout << "Enter account number: ";
        if (!(cin >> number)) {
            invalidInput();
            return;
        }

        Account* account = findAccount(number);

        if (account == nullptr) {
            cout << "Account not found.\n";
            return;
        }

        cout << "Enter deposit amount: Rs. ";
        if (!(cin >> amount)) {
            invalidInput();
            return;
        }

        account->deposit(amount);
    }

    void withdrawMoney() {
        int number;
        double amount;

        cout << "Enter account number: ";
        if (!(cin >> number)) {
            invalidInput();
            return;
        }

        Account* account = findAccount(number);

        if (account == nullptr) {
            cout << "Account not found.\n";
            return;
        }

        cout << "Enter withdrawal amount: Rs. ";
        if (!(cin >> amount)) {
            invalidInput();
            return;
        }

        account->withdraw(amount);
    }

    void transferMoney() {
        int fromNumber, toNumber;
        double amount;

        cout << "Enter sender account number: ";
        if (!(cin >> fromNumber)) {
            invalidInput();
            return;
        }

        cout << "Enter receiver account number: ";
        if (!(cin >> toNumber)) {
            invalidInput();
            return;
        }

        if (fromNumber == toNumber) {
            cout << "Sender and receiver accounts must be different.\n";
            return;
        }

        Account* sender = findAccount(fromNumber);
        Account* receiver = findAccount(toNumber);

        if (sender == nullptr || receiver == nullptr) {
            cout << "Sender or receiver account not found.\n";
            return;
        }

        cout << "Enter transfer amount: Rs. ";
        if (!(cin >> amount)) {
            invalidInput();
            return;
        }

        if (amount <= 0) {
            cout << "Invalid transfer amount.\n";
            return;
        }

        if (sender->balance < amount) {
            cout << "Insufficient balance!\n";
            return;
        }

        sender->balance -= amount;
        receiver->balance += amount;

        sender->history.emplace_back(
            "Transfer Sent", amount,
            "To account " + to_string(toNumber));

        receiver->history.emplace_back(
            "Transfer Received", amount,
            "From account " + to_string(fromNumber));

        cout << "Fund transfer successful!\n";
    }

    void accountInformation() {
        int number;

        cout << "Enter account number: ";
        if (!(cin >> number)) {
            invalidInput();
            return;
        }

        Account* account = findAccount(number);

        if (account == nullptr) {
            cout << "Account not found.\n";
            return;
        }

        account->showBalance();
    }

    void transactionHistory() {
        int number;

        cout << "Enter account number: ";
        if (!(cin >> number)) {
            invalidInput();
            return;
        }

        Account* account = findAccount(number);

        if (account == nullptr) {
            cout << "Account not found.\n";
            return;
        }

        account->showTransactions();
    }

    void listCustomers() const {
        if (customers.empty()) {
            cout << "No customers registered.\n";
            return;
        }

        for (int i = 0; i < static_cast<int>(customers.size()); i++) {
            customers[i].displayCustomer();

            for (int j = 0;
                 j < static_cast<int>(customers[i].accounts.size()); j++) {
                customers[i].accounts[j].showBalance();
            }
        }
    }

    static void invalidInput() {
        cout << "Invalid input. Please enter the correct data type.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
};

int main() {
    BankingSystem bank;
    int choice;

    cout << fixed << setprecision(2);

    do {
        cout << "\n========== BANKING SYSTEM ==========\n";
        cout << "1. Create Customer\n";
        cout << "2. Create Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Transfer Funds\n";
        cout << "6. View Account Information\n";
        cout << "7. View Transaction History\n";
        cout << "8. Display All Customers\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            BankingSystem::invalidInput();
            continue;
        }

        switch (choice) {
            case 1:
                bank.createCustomer();
                break;
            case 2:
                bank.createAccount();
                break;
            case 3:
                bank.depositMoney();
                break;
            case 4:
                bank.withdrawMoney();
                break;
            case 5:
                bank.transferMoney();
                break;
            case 6:
                bank.accountInformation();
                break;
            case 7:
                bank.transactionHistory();
                break;
            case 8:
                bank.listCustomers();
                break;
            case 9:
                cout << "Thank you for using our banking system!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}