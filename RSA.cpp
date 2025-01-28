#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to compute (base^exp) % mod using modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// Function to compute GCD of two numbers
long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to compute modular inverse of a number
long long modInverse(long long a, long long m) {
    long long m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        long long q = a / m;
        long long t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

// Function to generate the public and private keys (e, d, n)
void generateKeys(long long &e, long long &d, long long &n, long long p, long long q) {
    n = p * q;
    long long phi = (p - 1) * (q - 1);
    
    // Find e such that 1 < e < phi and gcd(e, phi) = 1
    e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) break;
        e++;
    }

    // Find d such that (d * e) % phi = 1
    d = modInverse(e, phi);
}

// Function to encrypt a message using the public key (e, n)
long long encrypt(long long m, long long e, long long n) {
    return modExp(m, e, n);
}

// Function to decrypt a message using the private key (d, n)
long long decrypt(long long c, long long d, long long n) {
    return modExp(c, d, n);
}

int main() {
    long long p, q, e, d, n;
    cout << "Enter two prime numbers p and q: ";
    cin >> p >> q;

    // Generate the RSA keys
    generateKeys(e, d, n, p, q);

    cout << "Public Key (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Private Key (d, n): (" << d << ", " << n << ")" << endl;

    // Encrypt a message (word to encrypt)
    string message;
    cout << "Enter the message to encrypt (as numbers): ";
    cin >> message;

    // Convert the message into numbers (ASCII values)
    long long encryptedMessage[message.length()];
    for (int i = 0; i < message.length(); i++) {
        encryptedMessage[i] = encrypt(message[i], e, n);
        cout << "Encrypted character " << message[i] << " -> " << encryptedMessage[i] << endl;
    }

    // Decrypt the message
    cout << "\nDecrypted message: ";
    for (int i = 0; i < message.length(); i++) {
        char decryptedChar = decrypt(encryptedMessage[i], d, n);
        cout << decryptedChar;
    }
    cout << endl;

    return 0;
}

//OUTPUT
// Enter two prime numbers p and q: 61 53
// Public Key (e, n): (17, 3233)
// Private Key (d, n): (2753, 3233)
// Enter the message to encrypt (as numbers): HELLO
// Encrypted character 72 -> 2170
// Encrypted character 69 -> 1634
// Encrypted character 76 -> 2170
// Encrypted character 76 -> 2170
// Encrypted character 79 -> 1598

// Decrypted message: HELLO