#include <bits/stdc++.h>
using namespace std;

/*
INTUITION (Greedy Approach):

We simulate the process of giving change at a lemonade stand.

Rules:
- Each lemonade costs $5
- Customers pay using 5, 10, or 20 dollar bills
- We must return correct change immediately

Key Idea:
We should ALWAYS try to save $5 bills because they are more useful.

Why?
- $10 can only be used in one way (for $20: 10 + 5)
- $5 can be used in multiple ways (for $10 and $20)

So for $20:
1. Prefer giving 10 + 5 (better strategy)
2. Otherwise give 3 × $5

Variables:
- five → number of $5 bills we have
- ten → number of $10 bills we have

If at any point we cannot give change → return false
*/

bool lemonadeChange(vector<int>& bills) {
    int five = 0;
    int ten = 0;

    for(int bill : bills) {

        // Case 1: Customer pays with $5
        if(bill == 5) {
            five++;
        }

        // Case 2: Customer pays with $10
        else if(bill == 10) {
            // Need to give $5 as change
            if(five > 0) {
                five--;
                ten++;
            } else {
                return false;
            }
        }

        // Case 3: Customer pays with $20
        else {
            // Prefer giving 10 + 5
            if(ten > 0 && five > 0) {
                ten--;
                five--;
            }
            // Otherwise give 3 × $5
            else if(five >= 3) {
                five -= 3;
            }
            else {
                return false;
            }
        }
    }

    return true;
}

int main() {
    int n;
    cout << "Enter number of customers: ";
    cin >> n;

    vector<int> bills(n);
    cout << "Enter bills (5, 10, 20): ";
    for(int i = 0; i < n; i++) {
        cin >> bills[i];
    }

    if(lemonadeChange(bills)) {
        cout << "True (Change can be given to all customers)\n";
    } else {
        cout << "False (Cannot give change to all customers)\n";
    }

    return 0;
}