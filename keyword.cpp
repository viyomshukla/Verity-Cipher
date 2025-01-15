#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
using namespace std;

unordered_map<char, char> createMapping(const string &keyword) {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string processedKey = keyword + alphabet;

    string cipherAlphabet;
    for (char c : processedKey) {
        c = toupper(c);
        if (cipherAlphabet.find(c) == string::npos) {
            cipherAlphabet += c;
        }
    }

    unordered_map<char, char> mapping;
    for (size_t i = 0; i < alphabet.size(); i++) {
        mapping[alphabet[i]] = cipherAlphabet[i];
    }

    return mapping;
}

string encryptKeywordCipher(const string &text, const unordered_map<char, char> &mapping) {
    string result;
    for (char c : text) {
        if (isalpha(c)) {
            char upper = toupper(c);
            result += mapping.at(upper);  
        } else {
            result += c;  
        }
    }
    return result;
}

string decryptKeywordCipher(const string &text, const unordered_map<char, char> &mapping) {
    unordered_map<char, char> reverseMapping;
    for (const auto &pair : mapping) {
        reverseMapping[pair.second] = pair.first;  
    }

    string result;
    for (char c : text) {
        if (isalpha(c)) {
            char upper = toupper(c);
            char decryptedChar = reverseMapping.at(upper);
            if (islower(c)) {
                result += tolower(decryptedChar);
            } else {
                result += decryptedChar;
            }
        } else {
            result += c; 
        }
    }
    return result;
}

string readFromFile(const string &filename) {
    ifstream file(filename);
    string content;
    if (file) {
        getline(file, content, '\0'); 
        file.close();
    } else {
        cout << "Error opening file!" << endl;
    }
    return content;
}

void keywordCipher() {
    cout << "=== Keyword Cipher ===\n";

    string keyword, text, fileChoice;
    cout << "Enter keyword(in capital letter): ";
    cin >> keyword;

    cout << "Do you want to (1) Enter text manually or (2) Read from file? ";
    cin >> fileChoice;

    if (fileChoice == "2") {
        string filename;
        cout << "Enter filename: ";
        cin >> filename;
        text = readFromFile(filename);
        if (text.empty()) {
            cout << "No content read from file." << endl;
            return;
        }
    } else {
        cout << "Enter text: ";
        cin.ignore(); 
        getline(cin, text);
    }

    auto mapping = createMapping(keyword);

    string encryptedText = encryptKeywordCipher(text, mapping);
    cout << "Encrypted Text: " << encryptedText << endl;

    string decryptedText = decryptKeywordCipher(encryptedText, mapping);
    cout << "Decrypted Text: " << decryptedText << endl;
}
