#include <iostream>
#include <vector>
#include <algorithm>  // for sort()
using namespace std;

class Solution {
public:
    void print_divisors(int n) {
        vector<int> ans;  // To store all divisors of n

        // Intuition:
        // A divisor of n is a number that divides n exactly (no remainder).
        // Divisors come in pairs: if i divides n, then (n / i) is also a divisor.
        // Example: for n = 36, when i = 2 → 36/2 = 18 → both 2 and 18 are divisors.
        
        int i = 1;
        while(i * i <= n) {  // We only need to go till sqrt(n)
            if(n % i == 0) {  // If i divides n
                ans.push_back(i);  // i is a divisor
                
                // To avoid adding the same divisor twice (for perfect squares)
                if(n / i != i) {
                    ans.push_back(n / i);  // Add the paired divisor
                }
            } 
            i++;
        }

        // Step 2: Sort the divisors in ascending order
        sort(ans.begin(), ans.end());
        
        // Step 3: Print all divisors
        cout << "Divisors of " << n << " are: ";
        for(int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    Solution sol;
    sol.print_divisors(n);

    return 0;
}
