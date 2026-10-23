#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

const string FILE_NAME = "users.txt";

bool userExists(const string& username) {
    ifstream file(FILE_NAME);
    string storedUser, storedPassword;

    while (file >> storedUser >> storedPassword) {
        if (storedUser == username) {
            return true;
        }
    }

    return false;
}

void registerUser() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    if (userExists(username)) {
        cout << "Error: Username already exists!\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    ofstream file(FILE_NAME, ios::app);

    if (!file) {
        cout << "Error: Unable to save user data.\n";
        return;
    }

    file << username << ' ' << password << '\n';
    file.close();

    cout << "Registration successful!\n";
}

void loginUser() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    ifstream file(FILE_NAME);

    if (!file) {
        cout << "Error: No registered users found.\n";
        return;
    }

    string storedUser, storedPassword;

    while (file >> storedUser >> storedPassword) {
        if (storedUser == username &&
            storedPassword == password) {
            cout << "Login successful! Welcome, "
                 << username << "!\n";
            return;
        }
    }

    cout << "Error: Invalid username or password.\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== LOGIN AND REGISTRATION SYSTEM =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            return 0;
        }

        switch (choice) {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
