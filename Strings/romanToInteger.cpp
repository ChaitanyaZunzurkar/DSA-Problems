#include <iostream>
#include <string>
using namespace std;

int romanToInt(string s) {
    int n = s.length();
    int value = 0;
    int i = 0;

    while (i < n) {
        if (i + 1 < n) {
            if (s[i] == 'I' && s[i + 1] == 'V') {
                value += 4;
                i += 2;
                continue;
            } else if (s[i] == 'I' && s[i + 1] == 'X') {
                value += 9;
                i += 2;
                continue;
            } else if (s[i] == 'X' && s[i + 1] == 'L') {
                value += 40;
                i += 2;
                continue;
            } else if (s[i] == 'X' && s[i + 1] == 'C') {
                value += 90;
                i += 2;
                continue;
            } else if (s[i] == 'C' && s[i + 1] == 'D') {
                value += 400;
                i += 2;
                continue;
            } else if (s[i] == 'C' && s[i + 1] == 'M') {
                value += 900;
                i += 2;
                continue;
            }
        }

        if (s[i] == 'I') value += 1;
        else if (s[i] == 'V') value += 5;
        else if (s[i] == 'X') value += 10;
        else if (s[i] == 'L') value += 50;
        else if (s[i] == 'C') value += 100;
        else if (s[i] == 'D') value += 500;
        else if (s[i] == 'M') value += 1000;

        i++;
    }

    return value;
}

int main() {
    string roman;
    cout << "Enter a Roman numeral: ";
    cin >> roman;

    int result = romanToInt(roman);
    cout << "Integer value: " << result << endl;

    return 0;
}
