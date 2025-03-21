#include <bits/stdc++.h>
using namespace std;

double Power(double a , int b) {
    long long exp = b;
    if(b < 0) {
        a = 1.0/a;
        exp = -exp;
    }
    
    double result = 1;
    while(exp > 0) {
        if(exp % 2 == 1) {
            result *= a;
        }
        a *= a;
        exp = exp / 2;
    }
    return result;
}

int main()
{
    double a;
    int b;
    cin >> a >> b;

    cout << Power(a , b) << endl;
    return 0;
}