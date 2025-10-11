#include <iostream>
using namespace std;

class Solution {
public:
    // -------------------------------
    // Method 1: Simple method (your code)
    // Checks each bit one by one
    // Time complexity: O(log n)
    // -------------------------------
    int setBitsSimple(int n) {
        int count = 0;
        while(n > 0) {
            if(n % 2 == 1) { // check if last bit is 1
                count++;
            }
            n /= 2; // remove the last bit
        }
        return count;
    }

    // -------------------------------
    // Method 2: Optimized method (bit manipulation)
    // Clears the rightmost set bit in each iteration
    // Time complexity: O(number of set bits)
    // -------------------------------
    int setBitsOptimized(int n) {
        int count = 0;
        while(n) {
            n = n & (n - 1); // clears the rightmost set bit
            count++;
        }
        return count;
    }
};

int main() {
    Solution sol;

    int n;
    cout << "Enter a number: ";
    cin >> n;

    // Using simple method
    int countSimple = sol.setBitsSimple(n);
    cout << "Number of set bits (simple method): " << countSimple << endl;

    // Using optimized method
    int countOptimized = sol.setBitsOptimized(n);
    cout << "Number of set bits (optimized method): " << countOptimized << endl;

    return 0;
}
