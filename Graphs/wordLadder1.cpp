#include <bits/stdc++.h>
using namespace std;

/*
========================================================
INTUITION (VERY IMPORTANT – READ THIS FIRST)
========================================================

This is the classic WORD LADDER problem.

1. Each word is treated as a NODE.
2. An EDGE exists between two words if they differ by
   EXACTLY ONE character.
3. We want the SHORTEST transformation sequence from
   beginWord to endWord.

Since:
- Each transformation costs the same (1 step)
- We need the SHORTEST path

👉 This is an UNWEIGHTED GRAPH shortest path problem.
👉 The correct approach is BFS (Breadth First Search).

--------------------------------------------------------
WHY BFS?
--------------------------------------------------------
BFS explores level-by-level.
Each level represents one transformation step.

So the FIRST time we reach endWord,
we are guaranteed it is the SHORTEST path.

--------------------------------------------------------
HOW BFS IS IMPLEMENTED HERE
--------------------------------------------------------

Queue stores:
    (currentWord, numberOfStepsSoFar)

unordered_set is used for:
    - Fast lookup (O(1))
    - To mark words as "visited" by erasing them

--------------------------------------------------------
TRANSFORMATION LOGIC
--------------------------------------------------------
For each word:
1. Change each character (one position at a time)
2. Try all letters from 'a' to 'z'
3. If the new word exists in the dictionary:
   - Push it into the queue
   - Remove it from the set (visited)

--------------------------------------------------------
WHEN TO STOP
--------------------------------------------------------
The moment we encounter endWord,
we return the current step count.

If queue becomes empty and endWord is never found,
answer is 0 (not reachable).

========================================================
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

        // Queue for BFS: (current word, steps taken so far)
        queue<pair<string, int>> q;
        q.push({beginWord, 1});

        // Convert word list to set for O(1) lookup
        unordered_set<string> st(wordList.begin(), wordList.end());

        // Remove beginWord if present to avoid revisiting
        st.erase(beginWord);

        // BFS starts
        while(!q.empty()) {

            string word = q.front().first;
            int steps = q.front().second;
            q.pop();

            // If endWord is reached, return steps
            if(word == endWord)
                return steps;

            // Try changing each character of the word
            for(int i = 0; i < word.size(); i++) {

                char original = word[i];

                // Try all letters from 'a' to 'z'
                for(char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;

                    // If the transformed word exists in set
                    if(st.find(word) != st.end()) {

                        // Mark visited
                        st.erase(word);

                        // Push into queue with +1 step
                        q.push({word, steps + 1});
                    }
                }

                // Restore original character
                word[i] = original;
            }
        }

        // If endWord is not reachable
        return 0;
    }
};

int main() {
    Solution sol;

    string beginWord, endWord;
    int n;

    cout << "Enter beginWord: ";
    cin >> beginWord;

    cout << "Enter endWord: ";
    cin >> endWord;

    cout << "Enter number of words in wordList: ";
    cin >> n;

    vector<string> wordList(n);
    cout << "Enter words:\n";
    for(int i = 0; i < n; i++) {
        cin >> wordList[i];
    }

    int result = sol.ladderLength(beginWord, endWord, wordList);

    cout << "Shortest transformation length: " << result << endl;

    return 0;
}