#include <iostream>
using namespace std;

class Solution {
public:
    int minBitFlips(int start, int goal) {
        int XOR = start ^ goal; // XOR gives 1 in positions where bits are different
        int count = 0;
        while (XOR > 0) {
            if (XOR % 2 == 1) { // Check if the last bit is 1
                count++;
            }
            XOR /= 2; // Shift right by dividing by 2
        }
        return count;
    }
};

int main() {
    Solution sol;
    
    int start = 10; // Example: 1010 in binary
    int goal = 7;   // Example: 0111 in binary
    
    // Intuition:
    // We want to count how many bits differ between start and goal.
    // XORing start and goal will give a number where each '1' represents a differing bit.
    // Counting the number of 1s in XOR gives the minimum bit flips required.
    
    int result = sol.minBitFlips(start, goal);
    
    cout << "Minimum bit flips to convert " << start << " to " << goal << " is: " << result << endl;
    
    return 0;
}
