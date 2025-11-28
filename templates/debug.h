#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace dbg {

inline void print_one(ostream& os, const string& s) { os << '"' << s << '"'; }
inline void print_one(ostream& os, const char* s) { print_one(os, string(s)); }
inline void print_one(ostream& os, bool b) { os << (b ? "true" : "false"); }

template <class A, class B>
void print_one(ostream& os, const pair<A,B>& p);

template <class T>
auto print_one(ostream& os, const T& x) -> decltype(os << x, void()) { os << x; }

template <class T>
auto print_one(ostream& os, const T& v) -> decltype(begin(v), end(v), void()) {
  os << "{";
  bool first = true;
  for (auto&& e : v) {
    if (!first) os << ", ";
    first = false;
    print_one(os, e);
  }
  os << "}";
}

template <class A, class B>
void print_one(ostream& os, const pair<A,B>& p) {
  os << "(";
  print_one(os, p.first);
  os << ", ";
  print_one(os, p.second);
  os << ")";
}

inline void out(ostream& os) { os << '\n'; }

template <class Head, class... Tail>
void out(ostream& os, Head&& h, Tail&&... t) {
  os << ' ';
  print_one(os, forward<Head>(h));
  out(os, forward<Tail>(t)...);
}

} // namespace dbg

#ifdef DEBUG
  #define debug(...) do { \
    cerr << "\033[31m" << "[" << __FILE__ << ":" << __LINE__ << "] (" << #__VA_ARGS__ << "):" << "\033[0m"; \
    dbg::out(cerr, __VA_ARGS__); \
  } while (0)
#else
  #define debug(...) do { } while (0)
#endif
