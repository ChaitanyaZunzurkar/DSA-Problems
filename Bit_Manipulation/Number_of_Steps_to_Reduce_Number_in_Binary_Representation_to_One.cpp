#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    /*
        INTUITION:
        If the binary number is even (ends with '0'),
        dividing by 2 in binary simply removes the last bit.
        Example: 1010 -> 101
    */
    void divideByTwo(string &s) {
        s.pop_back();  // remove last bit
    }

    /*
        INTUITION:
        If the binary number is odd (ends with '1'),
        we need to add 1 to make it even.
        Binary addition:
        - Flip trailing 1s to 0
        - Change the first 0 to 1
        - If all bits are 1, prepend '1'
        Example:
        111 -> 1000
        1011 -> 1100
    */
    void addOne(string &s) {
        int i = s.size() - 1;

        // handle carry propagation
        while (i >= 0 && s[i] == '1') {
            s[i] = '0';
            i--;
        }

        // if carry goes beyond MSB
        if (i < 0) {
            s = '1' + s;
        } else {
            s[i] = '1';
        }
    }

public:
    /*
        INTUITION:
        We repeatedly reduce the binary string to "1".

        Rules:
        - If last bit is '0' → even → divide by 2
        - If last bit is '1' → odd  → add 1

        Each operation counts as one step.
        Stop when the binary string becomes "1".
    */
    int numSteps(string s) {
        int operations = 0;

        while (s.size() > 1) {
            if (s.back() == '0') {
                divideByTwo(s);
            } else {
                addOne(s);
            }
            operations++;
        }

        return operations;
    }
};

int main() {
    string binary;
    cin >> binary;   // take binary string as input

    Solution obj;
    cout << obj.numSteps(binary) << endl;

    return 0;
}