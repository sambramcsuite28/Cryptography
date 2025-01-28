#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to extend the key to match the length of the text
string extendKey(const string &text, const string &key) {
    string extendedKey;
    int keyLength = key.length();
    int textLength = text.length();

    for (int i = 0; i < textLength; i++) {
        extendedKey += key[i % keyLength];
    }

    return extendedKey;
}

// Function to encrypt the plaintext using the Vigenere Cipher
string encryptVigenere(const string &plaintext, const string &key) {
    string ciphertext = "";
    string extendedKey = extendKey(plaintext, key);

    for (size_t i = 0; i < plaintext.length(); i++) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            char keyBase = islower(extendedKey[i]) ? 'a' : 'A';
            char encryptedChar = (plaintext[i] - base + extendedKey[i] - keyBase) % 26 + base;
            ciphertext += encryptedChar;
        } else {
            ciphertext += plaintext[i];
        }
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using the Vigenere Cipher
string decryptVigenere(const string &ciphertext, const string &key) {
    string plaintext = "";
    string extendedKey = extendKey(ciphertext, key);

    for (size_t i = 0; i < ciphertext.length(); i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            char keyBase = islower(extendedKey[i]) ? 'a' : 'A';
            char decryptedChar = (ciphertext[i] - base - (extendedKey[i] - keyBase) + 26) % 26 + base;
            plaintext += decryptedChar;
        } else {
            plaintext += ciphertext[i];
        }
    }

    return plaintext;
}

int main() {
    string plaintext, key, ciphertext;

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    cout << "Enter the key: ";
    getline(cin, key);

    ciphertext = encryptVigenere(plaintext, key);
    cout << "Encrypted text: " << ciphertext << endl;

    string decryptedText = decryptVigenere(ciphertext, key);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}