#ifdef DEBUG
#define debug(...) do { cerr << "[" << __LINE__ << "] " << #__VA_ARGS__ << " = "; _dbg(__VA_ARGS__); cerr << '\n'; } while(0)
template<class T> void _dbg(const T& x){ 
    cerr << x; 
}
template<class T, class... R> void _dbg(const T& x, const R&... r){ 
    cerr << x << ", "; 
    _dbg(r...); 
}
#else
#define debug(...) do { } while(0)
#endif
