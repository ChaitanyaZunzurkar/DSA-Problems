#include <iostream>
#include <climits>
using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        bool flag = false; // To mark if result should be negative

        // Edge case: overflow
        if(dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        // Quick return if divisor is 1
        if(divisor == 1) {
            return dividend;
        }

        // Convert to long long to avoid overflow when taking abs or shifting
        long long ldividend = dividend;
        long long ldivisor = divisor;

        // Determine the sign of the result
        if (ldividend < 0 && ldivisor < 0) {
            ldividend = labs(ldividend);
            ldivisor = labs(ldivisor);
        } else if(ldividend < 0) {
            ldividend = labs(ldividend);
            flag = true;
        } else if (ldivisor < 0) {
            ldivisor = labs(ldivisor);
            flag = true;
        }

        long long quotient = 0;

        // Main loop: subtract largest multiple of divisor until dividend < divisor
        while(ldividend >= ldivisor) {
            long long count = 0;

            // Find the maximum power of 2 such that (divisor << count) <= dividend
            while(ldividend >= (ldivisor << (count + 1))) {
                count++;
            }

            // Add that multiple to the quotient
            quotient += (1LL << count);

            // Reduce dividend
            ldividend -= (ldivisor << count);
        }

        // Apply sign
        if(flag) {
            return -quotient;
        }

        return quotient;
    }
};

int main() {
    int dividend, divisor;

    cout << "Enter dividend: ";
    cin >> dividend;

    cout << "Enter divisor: ";
    cin >> divisor;

    Solution sol;
    int result = sol.divide(dividend, divisor);

    cout << "Quotient: " << result << endl;

    return 0;
}
