#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

void generatePassword(int length, bool includeNumbers, bool includeSymbols, string &password) {
    const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char numbers[] = "0123456789";
    const char symbols[] = "!@#$%^&*()";
    string characters = letters;
    
    if (includeNumbers) {
        characters += numbers;
    }
    
    if (includeSymbols) {
        characters += symbols;
    }
    
    for (int i = 0; i < length; ++i) {
        password += characters[rand() % characters.length()];
    }
}

void displaySortedPasswords(const vector<string>& passwords) {
    vector<string> sortedPasswords = passwords;
    sort(sortedPasswords.begin(), sortedPasswords.end());
    
    cout << "Sorted Passwords" << endl;
    for (const auto &password : sortedPasswords) {
        cout << password << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    int passwordLength;
    bool includeNumbers, includeSymbols;
    vector<string> passwords;
    string choice;
    cout << "                                                  SIPAAHI - YOUR PASSBUDDY                                                                 "<< endl; 
    cout << "****------------------------------------------------------------------------------------------------------------------****"<< endl; 

    cout << "                                              Your owned Password Maker -                                                        "<< endl;
    cout << "SIPAAHI : -----Generate your customised password to keep your data safe   - " << endl;
    cout << "SIPAAHI : -----It will be my pleasure to serve you ..." << endl;

    do {
        string password;
        cout << "SIPAAHI : ---  What will be the length of the password: " << endl;
        cin >> passwordLength;
        
        cout << "SIPAAHI : ---  May I include numerical elements? (1 for yes, 0 for no): " << endl;
        cin >> includeNumbers;
        
        cout << "SIPAAHI : ---  Suggestion! Add symbols for strong password creation. May I do it for you? (1 for yes, 0 for no): " << endl;
        cin >> includeSymbols;

        // Clear input stream state and ignore remaining characters in the buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        generatePassword(passwordLength, includeNumbers, includeSymbols, password);
        passwords.push_back(password);
        
        cout << "Bravo, it's a strong password! PASSWORD: " << password << endl;
        cout << "Generate another password? (yes/no): " << endl;
        cin >> choice;
        
        // Clear input stream state and ignore remaining characters in the buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    } while (choice == "yes");
    
    displaySortedPasswords(passwords);
    
    return 0;
}
