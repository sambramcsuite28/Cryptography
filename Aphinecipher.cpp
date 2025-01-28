#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to compute modular inverse of 'a' under modulo 'm'
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // No modular inverse exists
}

// Encrypt function
string affineEncrypt(string plaintext, int a, int b) {
    string ciphertext = "";
    for (char c : plaintext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char encryptedChar = ((a * (c - base) + b) % 26) + base;
            ciphertext += encryptedChar;
        } else {
            ciphertext += c; // Leave non-alphabetic characters unchanged
        }
    }
    return ciphertext;
}

// Decrypt function
string affineDecrypt(string ciphertext, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        cerr << "Error: 'a' has no modular inverse under modulo 26. Choose another value.\n";
        return "";
    }

    string plaintext = "";
    for (char c : ciphertext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char decryptedChar = (a_inv * (c - base - b + 26) % 26) + base;
            plaintext += decryptedChar;
        } else {
            plaintext += c; // Leave non-alphabetic characters unchanged
        }
    }
    return plaintext;
}

// Main function to take user input and demonstrate encryption and decryption
int main() {
    string message;
    int a, b;

    cout << "Enter the message to encrypt: ";
    getline(cin, message);

    cout << "Enter key 'a' (must be coprime with 26): ";
    cin >> a;

    cout << "Enter key 'b': ";
    cin >> b;

    // Validate key 'a' for coprimeness with 26
    if (modInverse(a, 26) == -1) {
        cout << "Invalid key 'a'. It must be coprime with 26. Please try again.\n";
        return 1;
    }

    string encryptedMessage = affineEncrypt(message, a, b);
    string decryptedMessage = affineDecrypt(encryptedMessage, a, b);

    cout << "\nOriginal Message:  " << message;
    cout << "\nEncrypted Message: " << encryptedMessage;
    cout << "\nDecrypted Message: " << decryptedMessage << endl;

    return 0;
}

//Output
/*Enter the message to encrypt: AffineCipher
Enter key 'a' (must be coprime with 26): 5
Enter key 'b': 8

Original Message:  AffineCipher
Encrypted Message: IxxqvqKxhnqv
Decrypted Message: AffineCipher
*/