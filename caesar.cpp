#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void caesarCipher() {
    cout << "=== Caesar Cipher ===\n";
    string text;
    int shift;
    int option;

    cout << "Choose an option:\n";
    cout << "1. Encrypt text\n";
    cout << "2. Decrypt text\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> option;

    int inputOption;
    if (option == 1) {
        cout << "=== Encryption ===\n";
    } else if (option == 2) {
        cout << "=== Decryption ===\n";
    } else {
        cerr << "Invalid option. Exiting...\n";
        return;
    }

    cout << "Choose input method:\n";
    cout << "1. Enter text manually\n";
    cout << "2. Read text from file\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> inputOption;

    if (inputOption == 1) {
        cout << "Enter text: ";
        cin.ignore(); 
        getline(cin, text);
    } else if (inputOption == 2) {
        string inputFileName;
        cout << "Enter the input file name: ";
        cin >> inputFileName;

        ifstream inputFile(inputFileName);
        if (!inputFile.is_open()) {
            cerr << "Error: Unable to open file " << inputFileName << endl;
            return;
        }

        getline(inputFile, text, '\0'); 
        inputFile.close();
        cout << "Text read from file: " << text << endl;
    } else {
        cerr << "Invalid option. Exiting...\n";
        return;
    }

    cout << "Enter shift value: ";
    cin >> shift;

    shift = shift % 26; 

    for (char &c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            if (option == 1) {
                c = (c - base + shift + 26) % 26 + base; 
            } else {
                c = (c - base - shift + 26) % 26 + base; 
            }
        }
    }

    if (option == 1) {
        cout << "Encrypted Text: " << text << endl;
    } else {
        cout << "Decrypted Text: " << text << endl;
    }

    cout << "Do you want to save the result to a file? (y/n): ";
    char saveOption;
    cin >> saveOption;

    if (tolower(saveOption) == 'y') {
        string outputFileName;
        cout << "Enter the output file name: ";
        cin >> outputFileName;

        ofstream outputFile(outputFileName);
        if (!outputFile.is_open()) {
            cerr << "Error: Unable to open file " << outputFileName << endl;
            return;
        }

        outputFile << text;
        outputFile.close();
        if (option == 1) {
            cout << "Encrypted text saved to " << outputFileName << endl;
        } else {
            cout << "Decrypted text saved to " << outputFileName << endl;
        }
    }
}
