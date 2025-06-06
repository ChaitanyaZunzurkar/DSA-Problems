#include <iostream>
#include <string>
#include <climits>  // For INT_MAX and INT_MIN
using namespace std;

int myAtoi(string s) {
    int i = 0, n = s.length();
    long result = 0;
    int sign = 1;

    // 1. Skip leading whitespaces
    while (i < n && s[i] == ' ') i++;

    // 2. Check for optional '+' or '-' sign
    if (i < n && (s[i] == '+' || s[i] == '-')) {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    // 3. Process digits and build the result
    while (i < n && isdigit(s[i])) {
        result = result * 10 + (s[i] - '0');

        // 4. Clamp to int range if overflow occurs
        if (sign == 1 && result > INT_MAX) return INT_MAX;
        if (sign == -1 && -result < INT_MIN) return INT_MIN;

        i++;
    }

    return static_cast<int>(sign * result);
}

int main() {
    string input;
    cout << "Enter a number string: ";
    cin >> input;

    int number = myAtoi(input);
    cout << "Converted integer: " << number << endl;

    return 0;
}
