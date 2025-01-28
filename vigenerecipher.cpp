#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to extend the key to match the length of the message
string extendKey(const string &message, const string &key) {
    string extendedKey = key;
    while (extendedKey.length() < message.length()) {
        extendedKey += key;
    }
    return extendedKey.substr(0, message.length());
}

// Function to encrypt the message using the Vigenère cipher
string vigenereEncrypt(const string &message, const string &key) {
    string encryptedText = "";
    string extendedKey = extendKey(message, key);

    for (size_t i = 0; i < message.length(); i++) {
        if (isalpha(message[i])) {
            char base = isupper(message[i]) ? 'A' : 'a';
            char shift = isupper(extendedKey[i]) ? 'A' : 'a';
            char encryptedChar = ((message[i] - base + extendedKey[i] - shift) % 26) + base;
            encryptedText += encryptedChar;
        } else {
            encryptedText += message[i]; // Keep non-alphabetic characters unchanged
        }
    }
    return encryptedText;
}

// Function to decrypt the message using the Vigenère cipher
string vigenereDecrypt(const string &encryptedText, const string &key) {
    string decryptedText = "";
    string extendedKey = extendKey(encryptedText, key);

    for (size_t i = 0; i < encryptedText.length(); i++) {
        if (isalpha(encryptedText[i])) {
            char base = isupper(encryptedText[i]) ? 'A' : 'a';
            char shift = isupper(extendedKey[i]) ? 'A' : 'a';
            char decryptedChar = ((encryptedText[i] - base - (extendedKey[i] - shift) + 26) % 26) + base;
            decryptedText += decryptedChar;
        } else {
            decryptedText += encryptedText[i]; // Keep non-alphabetic characters unchanged
        }
    }
    return decryptedText;
}

int main() {
    string message, key;

    cout << "Enter the message to encrypt: ";
    getline(cin, message);

    cout << "Enter the encryption key: ";
    cin >> key;

    // Convert key to uppercase for consistency
    for (char &c : key) {
        c = toupper(c);
    }

    string encryptedMessage = vigenereEncrypt(message, key);
    string decryptedMessage = vigenereDecrypt(encryptedMessage, key);

    cout << "\nOriginal Message:  " << message;
    cout << "\nEncryption Key:    " << key;
    cout << "\nEncrypted Message: " << encryptedMessage;
    cout << "\nDecrypted Message: " << decryptedMessage << endl;

    return 0;
}

//OUTPUT
/*Enter the message to encrypt: HELLOVIGENERE
Enter the encryption key: KEY

Original Message:  HELLOVIGENERE
Encryption Key:    KEY
Encrypted Message: RIJVSUYVJYVIQ
Decrypted Message: HELLOVIGENERE
*/ 