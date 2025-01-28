#include <iostream>
using namespace std;

// Function to implement the Extended Euclidean Algorithm
int extendedEuclidean(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a; // gcd of (a, b) is a when b = 0
    }

    int x1, y1; // To store results of recursive call
    int gcd = extendedEuclidean(b, a % b, x1, y1);

    // Update x and y using results of the recursive call
    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

int main() {
    int a, b;
    cout << "Enter two integers (a and b): ";
    cin >> a >> b;

    int x, y;
    int gcd = extendedEuclidean(a, b, x, y);

    cout << "GCD: " << gcd << endl;
    cout << "Coefficients x and y (Bezout's identity): " << x << " and " << y << endl;

    return 0;
}
