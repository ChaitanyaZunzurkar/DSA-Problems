#include <iostream>
#include <string>
#include <climits>  
using namespace std;

int myAtoi(string s) {
    int i = 0, n = s.length();
    long result = 0;
    int sign = 1;

    while (i < n && s[i] == ' ') i++;

    if (i < n && (s[i] == '+' || s[i] == '-')) {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    while (i < n && isdigit(s[i])) {
        result = result * 10 + (s[i] - '0');

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
