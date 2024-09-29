#include <bits/stdc++.h>
using namespace std;

bool isValid(string s)
{
    stack<int> st;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
        {
            st.push(s[i]);
        }
        else if (!st.empty() && st.top() == '(' && s[i] == ')')
        {
            st.pop();
        }
        else if (!st.empty() && st.top() == '{' && s[i] == '}')
        {
            st.pop();
        }
        else if (!st.empty() && st.top() == '[' && s[i] == ']')
        {
            st.pop();
        }
        else
        {
            return false;
        }
    }

    if (st.empty())
    {
        return true;
    }
    return false;
}

int main()
{
    string str;
    cin >> str;
    if(isValid(str)) {
        cout << "true" << endl;
    }else {
        cout << "false" << endl;
    }
    return 0;
}