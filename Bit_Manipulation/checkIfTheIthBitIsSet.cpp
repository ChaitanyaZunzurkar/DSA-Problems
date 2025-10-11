#include <iostream>
using namespace std;

class Solution {
public:
    bool checkKthBit(int n, int k) {
        /*
            Intuition:
            ------------
            - Each bit in a number represents a power of 2.
            - To check if the kth bit (0-based index) is set:
                1. Create a mask by shifting 1 left by k positions → (1 << k)
                   Example: if k = 2 → mask = 00000100 (binary)
                2. Perform bitwise AND with n → n & mask
                   - If the result is non-zero → kth bit is 1
                   - If result is zero → kth bit is 0
        */
        if (n & (1 << k)) {
            return true;   // kth bit is set (1)
        }
        return false;      // kth bit is not set (0)
    }
};

int main() {
    int n, k;
    cout << "Enter number (n): ";
    cin >> n;
    cout << "Enter bit index (k): ";
    cin >> k;

    Solution ob;
    if (ob.checkKthBit(n, k))
        cout << "Yes, " << k << "th bit is set (1)." << endl;
    else
        cout << "No, " << k << "th bit is not set (0)." << endl;

    return 0;
}
