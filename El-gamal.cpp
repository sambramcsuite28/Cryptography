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

// Function to compute the modular inverse of a number modulo p
long long modInverse(long long a, long long p) {
    long long m0 = p, y = 0, x = 1;
    if (p == 1) return 0;
    while (a > 1) {
        long long q = a / p;
        long long t = p;
        p = a % p;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

// El-Gamal Key Generation (public key: e1, private key: d)
void generateKeys(long long &e1, long long &d, long long &p, long long &g) {
    // For simplicity, we use small values for p and g.
    p = 101;  // Large prime number
    g = 2;    // Primitive root modulo p

    // Select a private key d
    d = 15;  // Choose a secret private key

    // Calculate public key e1 = g^d % p
    e1 = modExp(g, d, p);
}

// El-Gamal Encryption function
void encrypt(long long m, long long e1, long long p, long long g, long long &c1, long long &c2, long long &r) {
    // Select a random number r
    r = rand() % (p - 1) + 1;  // Random value for r such that 1 < r < p-1

    // Compute c1 = g^r % p
    c1 = modExp(g, r, p);

    // Compute c2 = m * e1^r % p
    c2 = (m * modExp(e1, r, p)) % p;
}

// El-Gamal Decryption function
long long decrypt(long long c1, long long c2, long long d, long long p) {
    // Compute (c1^d) % p
    long long s = modExp(c1, d, p);

    // Compute the modular inverse of s
    long long sInverse = modInverse(s, p);

    // Decrypt the message m = (c2 * sInverse) % p
    return (c2 * sInverse) % p;
}

int main() {
    srand(time(0));  // Initialize random seed

    long long p, g, e1, d, m, c1, c2, r;

    // Key Generation
    generateKeys(e1, d, p, g);
    cout << "Public Key (e1, p): (" << e1 << ", " << p << ")" << endl;
    cout << "Private Key (d): " << d << endl;

    // User input for the message to encrypt
    cout << "Enter the message to encrypt (as a number): ";
    cin >> m;

    // Encryption
    encrypt(m, e1, p, g, c1, c2, r);
    cout << "Encrypted message (c1, c2): (" << c1 << ", " << c2 << ")" << endl;

    // Decryption
    long long decryptedMessage = decrypt(c1, c2, d, p);
    cout << "Decrypted message: " << decryptedMessage << endl;

    return 0;
}


//OUTPUT
// Enter the message to encrypt (as a number): 42

// Public Key (e1, p): (2, 101)
// Private Key (d): 15
// Encrypted message (c1, c2): (49, 8)
// Decrypted message: 42