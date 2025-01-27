#include <iostream>
#include <map>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

void saveConversionToFile(const string& fromCurrency, double amount, double convertedAmount) {
    ofstream outFile("conversion_history.txt", ios::app); // Open in append mode
    if (outFile.is_open()) {
        outFile << amount << " " << fromCurrency << " = " << convertedAmount << " BDT\n";
        outFile.close();
        cout << "Conversion saved to file.\n";
    } else {
        cout << "Error: Could not save conversion to file.\n";
    }
}

void saveRatesToFile(const map<string, double>& exchangeRates) {
    ofstream outFile("exchange_rates.txt");
    if (outFile.is_open()) {
        for (const auto& pair : exchangeRates) {
            outFile << pair.first << " " << pair.second << endl;
        }
        outFile.close();
        cout << "Exchange rates saved to file.\n";
    } else {
        cout << "Error: Could not save exchange rates to file.\n";
    }
}

void updateRates(map<string, double>& exchangeRates) {
    string currency;
    double rate;
    cout << "\nEnter the currency code and the new rate (e.g., USD 85.50): ";
    cin >> currency >> rate;
    if (exchangeRates.find(currency) != exchangeRates.end()) {
        exchangeRates[currency] = rate;
        cout << "Updated rate for " << currency << " is now " << rate << endl;
        saveRatesToFile(exchangeRates);
    } else {
        cout << "Currency code not recognized. No update performed.\n";
    }
}

void convertCurrency(const map<string, double>& exchangeRates) {
    string fromCurrency;
    double amount, convertedAmount;

    cout << "Enter the currency code you are converting from (e.g., USD): ";
    cin >> fromCurrency;
    if (exchangeRates.find(fromCurrency) == exchangeRates.end()) {
        cout << "Currency code is invalid. Please enter a valid code.\n";
        return;
    }
    cout << "Enter the amount to convert from " << fromCurrency << " to BDT: ";
    cin >> amount;

    convertedAmount = amount * exchangeRates.at(fromCurrency);
    cout << fixed << setprecision(2);
    cout << amount << " " << fromCurrency << " = " << convertedAmount << " BDT\n";

    saveConversionToFile(fromCurrency, amount, convertedAmount);
}

void displayConversionTable(const map<string, double>& exchangeRates) {
    cout << "\nCurrency Conversion Table (1 Unit to BDT):\n";
    cout << "--------------------------------------------\n";
    cout << left << setw(10) << "Currency" << setw(15) << "Rate to BDT" << endl;
    cout << "--------------------------------------------\n";
    for (const auto& pair : exchangeRates) {
        cout << left << setw(10) << pair.first << setw(15) << fixed << setprecision(2) << pair.second << endl;
    }
    cout << "--------------------------------------------\n";
}

int main() {
    map<string, double> exchangeRates{
        {"USD", 84.32},
        {"EURO", 101.25},
        {"AUD", 60.47},
        {"GBP", 115.50},
        {"JPY", 0.75},
        {"BDT", 1.0}
    };

    int choice;

    cout << "Welcome to the Simple BDT Currency Converter\n";

    do {
        cout << "\n1. Convert Currency\n2. Update Exchange Rates\n3. Display Conversion Table\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                convertCurrency(exchangeRates);
                break;
            case 2:
                updateRates(exchangeRates);
                break;
            case 3:
                displayConversionTable(exchangeRates);
                break;
            case 4:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please select a valid option.\n";
        }
    } while (true);

    return 0;
}
