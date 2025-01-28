#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Function to compute GCD (Greatest Common Divisor)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to compute modular exponentiation
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) // If exp is odd
            result = (result * base) % mod;
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod;
    }
    return result;
}

// Function to compute modular inverse using Extended Euclidean Algorithm
int modularInverse(int e, int phi) {
    int x, y;
    auto extendedEuclidean = [](int a, int b, int &x, int &y) -> int {
        if (b == 0) {
            x = 1, y = 0;
            return a;
        }
        int x1, y1;
        int gcd = extendedEuclidean(b, a % b, x1, y1);
        x = y1;
        y = x1 - (a / b) * y1;
        return gcd;
    };

    int gcd = extendedEuclidean(e, phi, x, y);
    if (gcd != 1) {
        cout << "Modular inverse does not exist!" << endl;
        return -1;
    }
    return (x % phi + phi) % phi;
}

int main() {
    // Step 1: Select two prime numbers p and q
    int p = 61, q = 53; // You can change these values
    int n = p * q;      // Calculate n
    int phi = (p - 1) * (q - 1); // Calculate Euler's totient function

    // Step 2: Choose e such that 1 < e < phi and gcd(e, phi) = 1
    int e = 17; // Commonly used value
    while (gcd(e, phi) != 1) {
        e++;
    }

    // Step 3: Compute d (modular inverse of e)
    int d = modularInverse(e, phi);

    // Display the public and private keys
    cout << "Public Key (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Private Key (d, n): (" << d << ", " << n << ")" << endl;

    // Step 4: Encryption
    string plaintext;
    cout << "Enter a word to encrypt: ";
    cin >> plaintext;

    vector<int> encrypted;
    cout << "Encrypted message: ";
    for (char ch : plaintext) {
        int encryptedChar = modExp((int)ch, e, n);
        encrypted.push_back(encryptedChar);
        cout << encryptedChar << " ";
    }
    cout << endl;

    // Step 5: Decryption
    cout << "Decrypted message: ";
    for (int encryptedChar : encrypted) {
        char decryptedChar = (char)modExp(encryptedChar, d, n);
        cout << decryptedChar;
    }
    cout << endl;

    return 0;
}
