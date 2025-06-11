#include <bits/stdc++.h>
using namespace std;

int getMax(int freq[])
{
    int maxCount = INT_MIN;
    for (int i = 0; i < 26; i++)
    {
        maxCount = max(maxCount, freq[i]);
    }
    return maxCount;
}

int getMin(int freq[])
{
    int minCount = INT_MAX;
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] > 0)
        {
            minCount = min(minCount, freq[i]);
        }
    }
    return minCount;
}

int beautySum(string s)
{
    int result = 0;
    for (int i = 0; i < s.length(); i++)
    {
        int freq[26] = {0};
        for (int j = i; j < s.length(); j++)
        {
            freq[s[i] - 'a']++;
            int beauty = getMax(freq) - getMin(freq);
            result += beauty;
        }
    }
    return result;
}

int main()
{
    string s;
    cin >> s;

    cout << beautySum(s) << endl;
    return 0;
}