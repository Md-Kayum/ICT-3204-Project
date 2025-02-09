#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;


void registerUser() {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    cout << "Enter a new password: ";
    cin >> password;

    ofstream usersFile("users.txt", ios::app);
    if (usersFile.is_open()) {
        usersFile << username << " " << password << endl;
        usersFile.close();
        cout << "User registered successfully!\n";
    } else {
        cout << "Error: Could not open the users file.\n";
    }
}


string loginUser() {
    string username, password, storedUsername, storedPassword;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ifstream usersFile("users.txt");
    if (usersFile.is_open()) {
        while (usersFile >> storedUsername >> storedPassword) {
            if (storedUsername == username && storedPassword == password) {
                cout << "Login successful! Welcome, " << username << "!\n";
                usersFile.close();
                return username;
            }
        }
        usersFile.close();
    } else {
        cout << "Error: Could not open the users file.\n";
    }

    cout << "Invalid username or password. Please try again.\n";
    return "";
}


void saveConversionToFile(string username, string fromCurrency, double amount, double convertedAmount) {
    ofstream outFile("conversion_history_" + username + ".txt", ios::app);
    if (outFile.is_open()) {
        outFile << amount << " " << fromCurrency << " = " << convertedAmount << " BDT\n";
        outFile.close();
        cout << "Conversion saved to your history file.\n";
    } else {
        cout << "Error: Could not save conversion to your history file.\n";
    }
}


void displayConversionHistory(string username) {
    ifstream inFile("conversion_history_" + username + ".txt");
    if (inFile.is_open()) {
        string line;
        cout << "\nYour Conversion History:\n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "No conversion history found for this user.\n";
    }
}


void userMenu(string username, map<string, double> exchangeRates) {
    while (true) {
        int choice;
        cout << "\n1. Convert Currency\n2. View Conversion History\n3. Logout\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string fromCurrency;
            double amount;
            cout << "Enter the currency code you are converting from (e.g., USD): ";
            cin >> fromCurrency;

            if (exchangeRates.find(fromCurrency) == exchangeRates.end()) {
                cout << "Currency code is invalid. Please enter a valid code.\n";
            } else {
                cout << "Enter the amount to convert from " << fromCurrency << " to BDT: ";
                cin >> amount;
                double convertedAmount = amount * exchangeRates[fromCurrency];
                cout << fixed << setprecision(2);
                cout << amount << " " << fromCurrency << " = " << convertedAmount << " BDT\n";
                saveConversionToFile(username, fromCurrency, amount, convertedAmount);
            }
        } else if (choice == 2) {
            displayConversionHistory(username);
        } else if (choice == 3) {
            cout << "Logging out...\n";
            return;
        } else {
            cout << "Invalid choice. Please select a valid option.\n";
        }
    }
}

int main() {
    map<string, double> exchangeRates = {
        {"USD", 84.32},
        {"EURO", 101.25},
        {"AUD", 60.47},
        {"GBP", 115.50},
        {"JPY", 0.75},
        {"BDT", 1.0}
    };

    cout << "Welcome to the Currency Converter Application\n";

    while (true) {
        int choice;
        cout << "\n1. Login\n2. Register\n3. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string loggedInUser = loginUser();
            if (!loggedInUser.empty()) {
                userMenu(loggedInUser, exchangeRates);
            }
        } else if (choice == 2) {
            registerUser();
        } else if (choice == 3) {
            cout << "Exiting program. Goodbye!\n";
            return 0;
        } else {
            cout << "Invalid choice. Please select a valid option.\n";
        }
    }
}
