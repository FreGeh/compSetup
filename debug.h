#pragma once
#include <bits/stdc++.h>

using namespace std;

void dbg_out() { cerr << '\n'; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}

#define debug(...) \
    cerr << "\033[31m" << '[' << __FILE__ << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):" << "\033[0m", dbg_out(__VA_ARGS__)
