#include <iostream>
using namespace std;

class Solution {
public:
    bool isPowerOfTwo(int n) {
        /*
            Intuition:
            ------------
            - A number is a power of 2 if it has exactly ONE bit set in its binary form.
              Examples:
                1  -> 0001
                2  -> 0010
                4  -> 0100
                8  -> 1000
              All have only one '1'.

            - Trick: (n & (n - 1)) == 0
                → This expression becomes true ONLY for powers of 2.

            Why?
            -----
            - For any power of 2 (say n = 8):
                n     = 1000
                n - 1 = 0111
                ----------------
                n & (n - 1) = 0000  ✅ (zero means only one bit was set)

            - For non-powers of 2 (say n = 6):
                n     = 110
                n - 1 = 101
                ----------------
                n & (n - 1) = 100  ❌ (non-zero means multiple bits were set)

            - We also check n > 0 because:
                * Negative numbers or zero are not powers of 2.
        */
        if (n <= 0) return false;       // Handle non-positive cases

        if (n & (n - 1)) {              // If this is non-zero → not a power of 2
            return false;
        }

        return true;                    // If zero → power of 2
    }
};

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    Solution ob;
    if (ob.isPowerOfTwo(n))
        cout << n << " is a Power of 2." << endl;
    else
        cout << n << " is NOT a Power of 2." << endl;

    return 0;
}
