#include "bits/stdc++.h"
using namespace std;
#define ll long long

// Conditional compilation
#ifdef DEBUG
#include "debug.h"
#else
#define debug(...) do { } while(0)
#endif

void solve() {
    // Code for each testcase:
    // Example: Median Number (https://codeforces.com/contest/1760/problem/A)
    vector<int> array(3);
    for (int i = 0; i < 3; i++) {
        cin >> array[i];
    }
    sort(array.begin(), array.end());
    cout << array[1] << "\n";
}

int main() {
    ios::sync_with_stdio(false); 
#ifndef DEBUG
    cin.tie(nullptr);
#endif

    int tests;
    cin >> tests;

    while (tests-- > 0) solve();

    return 0;
}
