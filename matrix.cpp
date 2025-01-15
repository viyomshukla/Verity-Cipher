#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

int determinant(const vector<vector<int>> &matrix) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

vector<vector<int>> matrixInverse(const vector<vector<int>> &matrix, int mod) {
    int det = determinant(matrix);
    int detModInverse = modInverse(det % mod + mod, mod);

    vector<vector<int>> inverse(2, vector<int>(2, 0));
    inverse[0][0] = matrix[1][1];
    inverse[0][1] = -matrix[0][1];
    inverse[1][0] = -matrix[1][0];
    inverse[1][1] = matrix[0][0];

    for (auto &row : inverse) {
        for (auto &element : row) {
            element = ((element % mod) * detModInverse) % mod;
            if (element < 0)
                element += mod;
        }
    }

    return inverse;
}

vector<int> matrixMultiply(const vector<vector<int>> &matrix, const vector<int> &text, int mod) {
    vector<int> result(2, 0);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i] += matrix[i][j] * text[j];
        }
        result[i] %= mod;
    }
    return result;
}

void matrixEncryption() {
    cout << "=== Hill Cipher ===\n";
    int option;

    cout << "Choose an option:\n";
    cout << "1. Enter input manually\n";
    cout << "2. Read input from a file\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> option;

    vector<vector<int>> key(2, vector<int>(2, 0));
    string plaintext;

    if (option == 1) {
        cout << "Enter 2x2 key matrix (mod 26):\n";
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                cin >> key[i][j];
            }
        }

        cout << "Enter plaintext (length must be even): ";
        cin >> plaintext;
    } else if (option == 2) {
        string inputFileName;
        cout << "Enter the input file name: ";
        cin >> inputFileName;

        ifstream inputFile(inputFileName);
        if (!inputFile.is_open()) {
            cerr << "Error: Unable to open file " << inputFileName << endl;
            return;
        }

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                inputFile >> key[i][j];
            }
        }

        inputFile >> plaintext;
        inputFile.close();
    } else {
        cerr << "Invalid option. Exiting...\n";
        return;
    }

    if (plaintext.length() % 2 != 0) {
        plaintext += 'X';
    }

    vector<int> textNumerical;
    for (char c : plaintext) {
        textNumerical.push_back(toupper(c) - 'A');
    }

    string ciphertext;
    for (size_t i = 0; i < textNumerical.size(); i += 2) {
        vector<int> pair = {textNumerical[i], textNumerical[i + 1]};
        vector<int> encryptedPair = matrixMultiply(key, pair, 26);

        for (int value : encryptedPair) {
            ciphertext += (char)(value + 'A');
        }
    }

    cout << "Ciphertext: " << ciphertext << endl;

    vector<vector<int>> keyInverse = matrixInverse(key, 26);
    string decryptedText;
    for (size_t i = 0; i < textNumerical.size(); i += 2) {
        vector<int> pair = {ciphertext[i] - 'A', ciphertext[i + 1] - 'A'};
        vector<int> decryptedPair = matrixMultiply(keyInverse, pair, 26);

        for (int value : decryptedPair) {
            decryptedText += (char)(value + 'A');
        }
    }

    cout << "Decrypted Text: " << decryptedText << endl;

   
    cout << "Do you want to save the results to a file? (y/n): ";
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

        outputFile << "Ciphertext: " << ciphertext << endl;
        outputFile << "Decrypted Text: " << decryptedText << endl;
        outputFile.close();
        cout << "Results saved to " << outputFileName << endl;
    }
}
