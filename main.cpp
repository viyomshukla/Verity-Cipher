#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>  
#include "rsa.h"        
#include "caesar.h"     
#include "matrix.h"     
#include "playfair.h"   
#include "keyword.h"    

using namespace std;

bool verifyLogin(const string &username, const string &password) {
    ifstream file("users.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open user file.\n";
        return false;
    }

    string storedUsername, storedPassword;
    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username && storedPassword == password) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void registerUser() {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    cout << "Enter a new password: ";

    char ch;
    password = "";
    while ((ch = _getch()) != '\r') {  
        if (ch == '\b') {  
            if (password.length() > 0) {
                password.pop_back();
                cout << "\b \b"; 
            }
        } else {
            password += ch;
            cout << "*"; 
        }
    }

    ofstream file("users.txt", ios::app); 
    if (!file.is_open()) {
        cerr << "Error: Unable to open user file for writing.\n";
        return;
    }

    file << username << " " << password << endl;
    file.close();
    cout << "\nUser registered successfully! You can now log in.\n";
}

void displayMenu() {
    cout << "\n**************** SecureKey-Verity Cipher *****************\n";
    cout << "1. RSA Encryption\n";
    cout << "2. Caesar Cipher\n";
    cout << "3. Matrix Method (Hill Algorithm)\n";
    cout << "4. Playfair Cipher\n";
    cout << "5. Keyword Cipher\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    int option;
    cout << "********************Welcome to SecureKey-Verity Cipher*********************\n";
    cout << "1. Login\n";
    cout << "2. Sign Up\n";
    cout << "Choose an option: ";
    cin >> option;

    string username, password;
    if (option == 1) {
        // Login
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";

        char ch;
        password = "";
        while ((ch = _getch()) != '\r') {  
            if (ch == '\b') {  
                if (password.length() > 0) {
                    password.pop_back();
                    cout << "\b \b"; 
                }
            } else {
                password += ch;
                cout << "*";  
            }
        }

        if (!verifyLogin(username, password)) {
            cerr << "Invalid username or password. Exiting...\n";
            return 1;
        }
        cout << "\nLogin successful! Welcome, " << username << ".\n";
    } else if (option == 2) {
        // Sign Up
        registerUser();
        cout << "Please restart the program to log in.\n";
        return 0;
    } else {
        cerr << "Invalid option. Exiting...\n";
        return 1;
    }

    int choice;
    do {
        displayMenu();   
        cin >> choice;   

        switch (choice) {
            case 1:
                rsaEncryption();   
                break;
            case 2:
                caesarCipher();    
                break;
            case 3:
                matrixEncryption(); 
                break;
            case 4:
                playfairCipher();  
                break;
            case 5:
                keywordCipher();  
                break;
            case 0:
                cout << "Exiting... Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);  

    return 0;  
}
