#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    vector<int> primeFac(int n) {
        set<int> st;  // Using a set to store unique prime factors automatically sorted
        
        // Step 1: Divide n by 2 repeatedly
        // 2 is the only even prime number
        while(n % 2 == 0) {
            st.insert(2);  // Insert 2 as a prime factor
            n /= 2;        // Reduce n
        }
        
        // Step 2: Check for odd prime factors from 3 onwards
        // We only need to check up to sqrt(n)
        for(int i = 3; i * i <= n; i += 2) { // Increment by 2 to consider only odd numbers
            while(n % i == 0) {
                st.insert(i);  // i is a prime factor
                n /= i;        // Reduce n
            }
        }
        
        // Step 3: If n is still greater than 2, then n itself is prime
        if(n > 2) st.insert(n);
        
        // Step 4: Convert set to vector and return
        return vector<int> (st.begin(), st.end());
    }
};

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    Solution sol;
    vector<int> factors = sol.primeFac(n);

    cout << "Prime factors of " << n << " are: ";
    for(int f : factors) {
        cout << f << " ";
    }
    cout << endl;

    return 0;
}
