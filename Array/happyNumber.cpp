#include <iostream>
using namespace std;

class Solution {
public:
    bool isHappy(int n) {
        /*
        -----------------------------------------------------------
        Intuition:
        -----------------------------------------------------------
        A happy number is obtained by repeatedly replacing a number
        with the sum of the squares of its digits.

        Example:
        19
        -> 1² + 9² = 82
        -> 8² + 2² = 68
        -> 6² + 8² = 100
        -> 1² + 0² + 0² = 1

        If the process reaches 1, the number is happy.

        If it never reaches 1, the numbers start repeating and form
        a cycle.

        We detect this cycle using Floyd's Cycle Detection Algorithm
        (Tortoise and Hare).

        slow : moves one step at a time.
        fast : moves two steps at a time.

        Case 1:
        If fast reaches 1, the number is Happy.

        Case 2:
        If slow == fast before reaching 1, a cycle exists,
        therefore the number is Not Happy.

        Time Complexity : O(1)
        (Numbers quickly reduce to a small range.)

        Space Complexity : O(1)
        -----------------------------------------------------------
        */

        int slow = n;
        int fast = n;

        while (fast != 1) {
            slow = generateSquareSum(slow);

            fast = generateSquareSum(fast);
            fast = generateSquareSum(fast);

            if (slow == fast && slow != 1)
                return false;
        }

        return true;
    }

private:
    int generateSquareSum(int n) {
        int sum = 0;

        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }

        return sum;
    }
};

int main() {
    int n;

    cout << "Enter a number: ";
    cin >> n;

    Solution obj;

    if (obj.isHappy(n))
        cout << n << " is a Happy Number." << endl;
    else
        cout << n << " is NOT a Happy Number." << endl;

    return 0;
}