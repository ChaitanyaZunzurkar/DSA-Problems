#include <iostream>
using namespace std;

int setRightmostUnsetBit(int n) {
    // Intuition:
    // 1. We want to set the rightmost unset (0) bit in n.
    // 2. When we do (n + 1), all the bits from the rightmost 0 bit to the end get flipped.
    //    Example: n = 1010 (10 in decimal)
    //             n+1 = 1011 (11 in decimal)
    // 3. OR-ing n with (n+1) sets that rightmost 0 bit without affecting other bits.
    //    1010 | 1011 = 1011
    return n | (n + 1);
}

int main() {
    int n;
    cout << "Enter a non-negative number: ";
    cin >> n;

    int result = setRightmostUnsetBit(n);
    cout << "After setting rightmost unset bit: " << result << endl;

    return 0;
}
