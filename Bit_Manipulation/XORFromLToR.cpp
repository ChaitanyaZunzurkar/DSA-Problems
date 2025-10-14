#include <bits/stdc++.h>
using namespace std;

// Function to compute XOR from 0 to n in O(1) using pattern
int xorFrom0ToN(int n) {
    // The XOR from 0 to n follows a pattern based on n % 4
    if (n % 4 == 0) return n;       // 0^1^2^...^n = n when n % 4 == 0
    if (n % 4 == 1) return 1;       // 0^1^2^...^n = 1 when n % 4 == 1
    if (n % 4 == 2) return n + 1;   // 0^1^2^...^n = n+1 when n % 4 == 2
    return 0;                        // 0^1^2^...^n = 0 when n % 4 == 3
}

// Function to find XOR of range [L, R]
int findXOR(int L, int R) {
    // XOR(L..R) = XOR(0..R) ^ XOR(0..(L-1))
    return xorFrom0ToN(R) ^ xorFrom0ToN(L - 1);
}

int main() {
    int L, R;
    
    // Take input from user
    cout << "Enter L and R: ";
    cin >> L >> R;

    // Calculate XOR of range [L, R]
    int result = findXOR(L, R);

    // Print result
    cout << "XOR of numbers from " << L << " to " << R << " is: " << result << endl;

    /*
    Intuition:
    1. XOR from 0 to n has a repeating pattern every 4 numbers.
    2. XOR(L..R) can be found by cancelling out XOR(0..L-1) from XOR(0..R):
       XOR(L..R) = XOR(0..R) ^ XOR(0..(L-1))
    3. This gives O(1) time and O(1) space solution.
    */

    return 0;
}
