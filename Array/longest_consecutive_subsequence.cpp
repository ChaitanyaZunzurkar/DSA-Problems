#include <bits/stdc++.h>
using namespace std;

/*
INTUITION (Pointer-based approach):

1. First, sort the array so consecutive numbers come next to each other.
2. Maintain a "window" that represents the current consecutive sequence.
3. If the current element is the same as the previous one, skip it (duplicate).
4. If the current element is not consecutive, reset the start of the window.
5. The length of the current window gives the length of the current sequence.
6. Track the maximum window length seen so far.

This approach follows your original thinking but with cleaner handling.
*/
int longestConsecutive_pointer(vector<int> arr) {
    int n = arr.size();
    if (n == 0) return 0;

    sort(arr.begin(), arr.end());

    int start = 0;
    int longest = 1;

    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            continue; // skip duplicates
        }

        if (arr[i] != arr[i - 1] + 1) {
            start = i; // break in sequence
        }

        longest = max(longest, i - start + 1);
    }

    return longest;
}

/*
INTUITION (lastSmaller approach - Striver style):

1. After sorting, we build the sequence step by step.
2. "lastSmaller" stores the last number of the current consecutive sequence.
3. If current number == lastSmaller + 1, it extends the sequence.
4. If current number is equal to lastSmaller, it is a duplicate → ignore it.
5. Otherwise, the sequence is broken and we start a new one.
6. Keep updating the maximum length encountered.

This method avoids pointer complexity and is safer and cleaner.
*/
int longestConsecutive_lastSmaller(vector<int> arr) {
    int n = arr.size();
    if (n == 0) return 0;

    sort(arr.begin(), arr.end());

    int lastSmaller = INT_MIN;
    int count = 0;
    int longest = 1;

    for (int i = 0; i < n; i++) {
        if (arr[i] - 1 == lastSmaller) {
            count++;
            lastSmaller = arr[i];
        } 
        else if (arr[i] != lastSmaller) {
            count = 1;
            lastSmaller = arr[i];
        }

        longest = max(longest, count);
    }

    return longest;
}

/*
INTUITION (Using unordered_set – Optimal Approach):

1. Store all elements of the array in an unordered_set.
   - This automatically removes duplicates.
   - It allows O(1) average time lookups.

2. For each element in the set, check whether it can be the
   start of a consecutive sequence.
   - An element is a start if (element - 1) does NOT exist in the set.

3. Once a start is found, keep moving forward (element + 1, element + 2, ...)
   as long as the next consecutive element exists in the set.

4. Count the length of this sequence and update the maximum length found.

5. Since each number is processed at most once, the overall time complexity
   remains O(n).

This approach avoids sorting and is the most efficient solution.
*/
int longestConsecutive_set(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;

    unordered_set<int> st;
    for (int x : arr) {
        st.insert(x);
    }

    int longest = 1;

    for (auto it : st) {
        // Check if 'it' is the start of a sequence
        if (st.find(it - 1) == st.end()) {
            int count = 1;
            int x = it;

            // Extend the sequence as long as consecutive elements exist
            while (st.find(x + 1) != st.end()) {
                x++;
                count++;
            }

            longest = max(longest, count);
        }
    }

    return longest;
}

/*
Driver code to test both approaches.
*/
int main() {
    vector<int> arr = {100, 4, 200, 1, 3, 2, 2};

    cout << "Pointer-based Approach Result: "
         << longestConsecutive_pointer(arr) << endl;

    cout << "LastSmaller Approach Result: "
         << longestConsecutive_lastSmaller(arr) << endl;

    return 0;
}
