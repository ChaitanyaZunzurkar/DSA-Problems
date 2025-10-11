#include <iostream>
using namespace std;

class Solution {
public:
    bool isEven(int n) {
        /*
            Intuition:
            ------------
            - In binary form:
                * Even numbers always end with 0
                * Odd numbers always end with 1
            - So we can check the **least significant bit (LSB)**:
                * If (n & 1) == 1 → LSB is 1 → number is odd
                * If (n & 1) == 0 → LSB is 0 → number is even
            - This method avoids using modulo (%) and is faster at bit level.
        */
        if (n & 1) {
            return false;  // Odd number
        }
        return true;       // Even number
    }
};

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    Solution ob;
    if (ob.isEven(n))
        cout << n << " is Even." << endl;
    else
        cout << n << " is Odd." << endl;

    return 0;
}
