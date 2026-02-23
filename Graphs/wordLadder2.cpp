#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM: Word Ladder II

INTUITION:
-----------
We need to find ALL shortest transformation sequences from beginWord to endWord.
Each transformation can change only ONE character, and the word must exist in the dictionary.

APPROACH = BFS + DFS

1) BFS (Shortest Distance):
   - Treat each word as a node.
   - An edge exists if two words differ by one character.
   - BFS guarantees the shortest path.
   - Store the minimum level (distance) of each word in a map.

2) DFS (Backtracking):
   - Start from endWord and move backwards.
   - Only move to a word whose level is exactly one less.
   - This ensures ONLY shortest paths are generated.

WHY BOTH?
---------
- BFS finds the shortest length.
- DFS generates ALL paths of that shortest length.
*/

class Solution {
    unordered_map<string, int> mp;     // word -> shortest level
    vector<vector<string>> ans;         // stores all valid sequences
    string begin;                       // beginWord (DFS stopping point)

private:
    /*
    DFS to backtrack from endWord to beginWord
    */
    void dfs(string word, vector<string>& seq) {

        // Base case: reached beginWord
        if (word == begin) {
            reverse(seq.begin(), seq.end());
            ans.push_back(seq);
            reverse(seq.begin(), seq.end());
            return;
        }

        int steps = mp[word];
        int len = word.size();

        // Try all single-character transformations
        for (int i = 0; i < len; i++) {
            char original = word[i];

            for (char ch = 'a'; ch <= 'z'; ch++) {
                word[i] = ch;

                // Move only one level backward (shortest path condition)
                if (mp.find(word) != mp.end() && mp[word] + 1 == steps) {
                    seq.push_back(word);
                    dfs(word, seq);
                    seq.pop_back();
                }
            }
            word[i] = original;
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {

        begin = beginWord;   // DFS stopping condition

        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<string> q;

        // BFS initialization
        q.push(beginWord);
        mp[beginWord] = 1;
        st.erase(beginWord);

        int len = beginWord.size();

        /*
        BFS: calculate shortest distance of each word
        */
        while (!q.empty()) {
            string word = q.front();
            q.pop();

            int steps = mp[word];
            if (word == endWord) break;

            for (int i = 0; i < len; i++) {
                char original = word[i];

                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;

                    if (st.count(word)) {
                        q.push(word);
                        st.erase(word);
                        mp[word] = steps + 1;
                    }
                }
                word[i] = original;
            }
        }

        /*
        DFS: generate all shortest sequences
        */
        if (mp.find(endWord) != mp.end()) {
            vector<string> seq;
            seq.push_back(endWord);
            dfs(endWord, seq);
        }

        return ans;
    }
};

int main() {
    string beginWord, endWord;
    int n;

    cout << "Enter beginWord: ";
    cin >> beginWord;

    cout << "Enter endWord: ";
    cin >> endWord;

    cout << "Enter number of words in dictionary: ";
    cin >> n;

    vector<string> wordList(n);
    cout << "Enter words:\n";
    for (int i = 0; i < n; i++) {
        cin >> wordList[i];
    }

    Solution obj;
    vector<vector<string>> result = obj.findLadders(beginWord, endWord, wordList);

    cout << "\nAll shortest transformation sequences:\n";
    for (auto& path : result) {
        for (auto& word : path) {
            cout << word << " ";
        }
        cout << endl;
    }

    return 0;
}