#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse1(int e, int phi) {
    int t = 0, new_t = 1;
    int r = phi, new_r = e;

    while (new_r != 0) {
        int quotient = r / new_r;

        int temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;

        int temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }

    if (r > 1) {
        throw runtime_error("e is not invertible");
    }
    if (t < 0) {
        t += phi;
    }
    return t;
}

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

void rsaEncryption() {
    int p, q;

    cout << "Enter the first prime number (p): ";
    cin >> p;
    while (!isPrime(p)) {
        cout << "The number " << p << " is not a prime number. Try again: ";
        cin >> p;
    }

    cout << "Enter the second prime number (q): ";
    cin >> q;
    while (!isPrime(q)) {
        cout << "The number " << q << " is not a prime number. Try again: ";
        cin >> q;
    }

    int n = p * q;
    int phi = (p - 1) * (q - 1);

    int e = 3;
    while (e < phi && gcd(e, phi) != 1) {
        e++;
    }

    int d = modInverse1(e, phi);

    int message;
    cout << "Enter a message (integer less than " << n << "): ";
    cin >> message;

    int encrypted = modExp(message, e, n);
    int decrypted = modExp(encrypted, d, n);

    cout << "Public Key: (" << e << ", " << n << ")\n";
    cout << "Private Key: (" << d << ", " << n << ")\n";
    cout << "Original Message: " << message << "\n";
    cout << "Encrypted Message: " << encrypted << "\n";
    cout << "Decrypted Message: " << decrypted << "\n";
}
