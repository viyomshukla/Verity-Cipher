#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string removeDuplicates(const string &str) {
    string result;
    for (char c : str) {
        if (result.find(c) == string::npos)
            result += c;
    }
    return result;
}

vector<vector<char>> generateMatrix(const string &key) {
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    string processedKey = removeDuplicates(key + alphabet);

    vector<vector<char>> matrix(5, vector<char>(5));
    int index = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = processedKey[index++];
        }
    }
    return matrix;
}

pair<int, int> findPosition(const vector<vector<char>> &matrix, char c) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c)
                return make_pair(i, j);
        }
    }
    return make_pair(-1, -1);
}

string encryptPlayfair(const string &plaintext, const vector<vector<char>> &matrix) {
    string processedText;
    for (char c : plaintext) {
        if (c != ' ') {
            processedText += (toupper(c) == 'J') ? 'I' : toupper(c);
        }
    }
    if (processedText.length() % 2 != 0) {
        processedText += 'X';
    }

    string ciphertext;
    for (size_t i = 0; i < processedText.length(); i += 2) {
        char a = processedText[i];
        char b = processedText[i + 1];
        pair<int, int> pos1 = findPosition(matrix, a);
        pair<int, int> pos2 = findPosition(matrix, b);

        int row1 = pos1.first, col1 = pos1.second;
        int row2 = pos2.first, col2 = pos2.second;

        if (row1 == row2) {
            ciphertext += matrix[row1][(col1 + 1) % 5];
            ciphertext += matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            ciphertext += matrix[(row1 + 1) % 5][col1];
            ciphertext += matrix[(row2 + 1) % 5][col2];
        } else {
            ciphertext += matrix[row1][col2];
            ciphertext += matrix[row2][col1];
        }
    }

    return ciphertext;
}

string decryptPlayfair(const string &ciphertext, const vector<vector<char>> &matrix) {
    string plaintext;

    for (size_t i = 0; i < ciphertext.length(); i += 2) {
        char a = ciphertext[i];
        char b = ciphertext[i + 1];
        pair<int, int> pos1 = findPosition(matrix, a);
        pair<int, int> pos2 = findPosition(matrix, b);

        int row1 = pos1.first, col1 = pos1.second;
        int row2 = pos2.first, col2 = pos2.second;

        if (row1 == row2) {
            plaintext += matrix[row1][(col1 + 4) % 5];
            plaintext += matrix[row2][(col2 + 4) % 5];
        } else if (col1 == col2) {
            plaintext += matrix[(row1 + 4) % 5][col1];
            plaintext += matrix[(row2 + 4) % 5][col2];
        } else {
            plaintext += matrix[row1][col2];
            plaintext += matrix[row2][col1];
        }
    }

    return plaintext;
}

void playfairCipher() {
    cout << "=== Playfair Cipher ===\n";

    string key, plaintext, ciphertext;
    char option;

    cout << "Do you want to read input from a file? (y/n): ";
    cin >> option;

    if (option == 'y' || option == 'Y') {
        string filename;
        cout << "Enter the filename: ";
        cin >> filename;

        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        getline(inputFile, key);
        getline(inputFile, plaintext);
        inputFile.close();

        cout << "Key from file: " << key << endl;
        cout << "Plaintext from file: " << plaintext << endl;

    } else {
        cout << "Enter keyword(in capital letter): ";
        cin >> key;

        for (char c : key) {
            if (!isalpha(c)) {
                cerr << "Error: Keyword should only contain alphabetic characters!" << endl;
                return;
            }
        }

        cout << "Enter plaintext: ";
        cin.ignore();
        getline(cin, plaintext);

        for (char c : plaintext) {
            if (!isalpha(c) && c != ' ') {
                cerr << "Error: Plaintext should only contain alphabetic characters and spaces!" << endl;
                return;
            }
        }
    }

    auto matrix = generateMatrix(key);
    ciphertext = encryptPlayfair(plaintext, matrix);
    string decryptedText = decryptPlayfair(ciphertext, matrix);

    if (!ciphertext.empty()) {
        cout << "Ciphertext: " << ciphertext << endl;
        cout << "Decrypted Text: " << decryptedText << endl;
    }
}


