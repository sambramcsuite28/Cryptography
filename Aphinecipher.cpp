#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

using namespace std;

// Function to find the modular inverse of 'a' under modulo 'm'
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    throw invalid_argument("No modular inverse exists");
}

// Function to encrypt the plaintext using the Affine Cipher
string encryptAffine(string plaintext, int a, int b) {
    string ciphertext = "";

    // Encrypt each character
    for (char c : plaintext) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (a * (c - base) + b) % 26 + base;
        }
        ciphertext += c;
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using the Affine Cipher
string decryptAffine(string ciphertext, int a, int b) {
    string plaintext = "";

    // Find modular inverse of 'a'
    int a_inverse = modInverse(a, 26);

    // Decrypt each character
    for (char c : ciphertext) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (a_inverse * ((c - base) - b + 26)) % 26 + base;
        }
        plaintext += c;
    }

    return plaintext;
}

int main() {
    string plaintext, ciphertext;
    int a, b;

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    cout << "Enter the keys (a and b): ";
    cin >> a >> b;

    // Validate 'a' (it must be coprime with 26)
    if (__gcd(a, 26) != 1) {
        cerr << "Error: 'a' must be coprime with 26." << endl;
        return 1;
    }

    ciphertext = encryptAffine(plaintext, a, b);
    cout << "Encrypted text: " << ciphertext << endl;

    string decryptedText = decryptAffine(ciphertext, a, b);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
