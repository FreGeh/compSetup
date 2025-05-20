#include "bits/stdc++.h"
using namespace std;
#define ll long long

// Conditional compilation
#ifdef DEBUG
#include "debug.h"
#else
#define debug(...) \
    do             \
    {              \
    } while (0)
#endif

void operationA(int i, vector<char> &S)
{
    S.erase(S.begin() + i - 1);
}
void operationB(int i, char b, vector<char> &S)
{
    S.insert(S.begin() + i - 1, b);
}
void operationC(int i, int j, vector<char> &S)
{
    swap(S[i - 1], S[j - 1]);
}
bool palindromeCheck(vector<char> &S)
{
    return equal(S.begin(), S.begin() + S.size() / 2, S.rbegin());
}
int minNumb(vector<char> &S)
{
    //todo
}

void solve()
{
    int n, q; // length initial string, number of queries
    cin >> n >> q;

    string tmp;
    cin >> tmp;
    vector<char> S(tmp.begin(), tmp.end());

    vector<int> X(q);
    int counter = 0;
    for (int i = 0; i < q; i++)
    {
        int x;
        cin >> x;
        switch (x)
        {
        case 1:
            cout << (palindromeCheck(S) ? "yes" : "no");
            cout << endl;
            break;

        case 2:
            cout << minNumb(S) << endl;
            break;

        case 3:
        {
            int i;
            cin >> i;
            operationA(i, S);
            break;
        }
        case 4:
        {
            int i;
            char b;
            cin >> i >> b;
            operationB(i, b, S);
            break;
        }
        case 5:
        {
            int i, j;
            cin >> i >> j;
            operationC(i, j, S);
            break;
        }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
#ifndef DEBUG
    cin.tie(nullptr);
#endif

    int tests;
    cin >> tests;

    while (tests-- > 0)
        solve();

    return 0;
}
