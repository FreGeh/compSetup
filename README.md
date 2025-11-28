*See [Getting Started](./SETUP.md) to learn how to setup your environment and walk your first steps in the competitive programming world!*
# Practical Competitive Programming Handbook
- [Competition Basics](#competition-basics)
- [C++ Basics](#c-basic-overview)
- [Basic Datastructures](#basic-datastructures)
- [Algorithm Design](#algorithm-design)
- [Sort & Search](#sort--search)
- [Graphs](#graphs)
  - [Graph Structures](#structures)
  - [BFS](#breadth-first-search)
  - [DFS](#depth-first-search)
  - [Floyd-Warshall](#floyd-warshall)
  - [Dijkstra](#dijkstra)
- [Dynamic Programming](#dynamic-programming)
  - [Knapsack](#knapsack)
  - [Longest Subsequence](#longest-subsequence)
- [Advanced Datastructures](#advanced-datastructures)
  - [Trees](#trees)
- [Strings](#strings)
- [Geometry](#geometry)
- [Mathematics](#mathematics)

# Competition Basics

## Workflow
1. **Compile**: `g++ -std=gnu++20 -O2 -Wall -Wextra -pipe -g -fsanitize=address,undefined program.cpp -o program`
2. **Run**: `./program < input.txt`

If you want to add debug the code via `debug(...)` usages in the `program.cpp`, just add `-DDEBUG` to Compile Call

## Must Have Header
```cpp
#include "bits/stdc++.h"
using namespace std;
#define ll long long
```
## Fast I/O template
Inside main function, always add:
```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);
```

## Estimate Runtime
| Typical technique | Time complexity | Safe max |
|-------------------|----------------|----------|
| Binary exponentiation, binary search, GCD | $\mathcal O(\log n)$ | $n \le 10^{18}$ |
| Trial division, sieve of Eratosthenes | $\mathcal O(\sqrt n)$ | $n \le 10^{15}$ |
| Linear scan, two-pointer, cumulative sums | $\mathcal O(n)$ | $n \le 10^{8}$ |
| Sorting (merge sort, quicksort, heapsort) | $\mathcal O(n \log n)$ | $n \le 10^{6}$ |
| BFS / DFS on graph $(n+m)$ | $\mathcal O(n+m)$ | $n,m \le 2\cdot 10^{5}$ |
| Dijkstra / Prim (binary heap) | $\mathcal O(m \log n)$ | $n,m \le 2\cdot 10^{5}$ |
| Segment tree / Fenwick tree (updates + queries) | $\mathcal O\!\bigl((n+q)\log n\bigr)$ | $n,q \le 2\cdot 10^{5}$ |
| Mo’s algorithm, block decomposition | $\mathcal O(n\sqrt n)$ | $n \le 10^{5}$ |
| DP on pairs, prefix tables, double loop | $\mathcal O(n^{2})$ | $n \le 5000$ |
| Floyd–Warshall, cubic DP, matrix multiplication | $\mathcal O(n^{3})$ | $n \le 500$ |
| Bitmask DP / enumerate all subsets | $\mathcal O(2^{n})$ | $n \le 20$ |
| Backtracking all permutations | $\mathcal O(n!)$ | $n \le 11$ |

## Contest Learnings

- Really make sure you **fully read the problem description**, especially to discover properties which **limit possible result cases**

# C++ Basic Overview

## Input
- `cin >>` reads whole string till space
- `cin.get(c)` reads `char c`, also spaces and `\n`
- `getline(cin, s)` reads whole line as `string s`
- `vector<char> S(tmp.begin(), tmp.end())` seperates string into char vector

for $n$ numbers (crucial to not forget the `&`):
```cpp
int n;
cin >> n;
vector<int> A(n);
for (int &x : A) {
    cin >> x;
}
```

### for older USACO
put this at the top
```cpp
freopen("problemname.in", "r", stdin);
freopen("problemname.out", "w", stdout);
```

## Output
- `cout <<` standard
- `(statement ? "true" : "false")` to output a value depending on the bool value of the `statement`

## Math Tricks
- Round Up in fractions, use `a+b-1/b` instead of `a/b`.
- Square to avoid `sqrt`

## STL Tricks
```cpp
iota(v.begin(), v.end(), 0); // 0,1,2,...
accumulate(v.begin(), v.end(), 0LL); // sum
sort(v.begin(), v.end(), greater<>()); // descending
equal(v.begin(), v.begin()+n/2, v.rbegin()); // palindrome
A.erase(unique(A.begin(), A.end()), A.end()); // remove duplicates from vector
```

## Bit Manipulation

## Data Types
| Type | Size / Range | Notable properties |
|------|--------------|-------------------|
| `int` | $4\text{ B},\;[-2^{31},\,2^{31}\!-\!1]$ so about $2.15 \cdot 10^9$ | fastest arithmetic, default loop index |
| `long long` | $8\text{ B},\;\approx[-9{\times}10^{18},\,9{\times}10^{18}]$ | 64-bit signed, safe for most sums/products |
| `unsigned int` | $4\text{ B},\;[0,\,2^{32}\!-\!1]$ | wrap-around mod $2^{32}$; bit masks |
| `unsigned long long` | $8\text{ B},\;[0,\,2^{64}\!-\!1]$ | 64-bit unsigned, modular hashes |
| `double` | $8\text{ B},\;\sim15$ decimal digits | hardware FPU; geometry, probabilistic DP |
| `long double` (GCC) | $16\text{ B},\;\sim18$ digits | extra precision for numeric analysis |
| `char` | $1\text{ B},\;[0,255]$ | tiny integer; ASCII grids, bit tricks |
| `bool` | $1\text{ B}$ (bit-packed in `vector<bool>`) | logical flags, visited arrays |
| `size_t` | $8\text{ B},\;[0,\,2^{64}\!-\!1]$ | unsigned type returned by `sizeof`, container sizes |

## Coordinate Compression

When you need to process a lot ($>10^9$) of updates or queries on ranges $[l,r)$ you want to only consider those that are actually important and preprocess them in some way.

0. Determine amount of queries and prepare vectors outside of main function (e.g.`max_val=100005` for $1 \leq Q \leq 10^5$ queries.)
1. **Collect keys** which are decisive. Like `l` and `r` for range queries $[l,r)$ in an Indices Array `I`.
2. **Compress** via ***sorting*** + ***removing duplicates*** from `I` and implementing a `getIndex(x)=lower_bound(I.begin(), I.end(), x) - I.begin()` function.
3. Build **Segment Difference Array** `diff` for queries which update the values: (1-indexed) `diff[getIndex(l)+1] += v;` and where it ends `diff[getIndex(r)+1] -= v`
4. Determine **Segment Values** via `val[i] = val[i-1] + diff[i]`
5. When wanting to answer queries over different segments, you also need to save **width of each segment** `widths[i+1] = I[i+1] - I[i]`
6. Use that for example for ***Prefix sums*** `pre[i] = pre[i-1] + val[i] * widths[i]` 

# Basic Datastructures

| Container / Helper | Key operations & complexity | Typical contest use |
|--------------------|----------------------------|--------------------|
| `vector<T>` | Dynamic array, index/push_back $O(1)$ amortized | Arrays, graphs, DP tables |
| `deque<T>` | Push/pop front/back $O(1)$ | Sliding window, 0-1 BFS |
| `list<T>` | Insert/erase $O(1)$ with iterator | Rarely used; custom linked lists |
| `array<T,N>` | Fixed-size array, index $O(1)$ | Small static arrays, DP, geometry |
| `stack<T>` | LIFO push/pop/top $O(1)$ | DFS, parentheses checker |
| `queue<T>` | FIFO push/pop/front $O(1)$ | BFS, task scheduling |
| `priority_queue<T>` | Push/pop/top $O(log n)$ | Dijkstra, K-largest elements |
| `set<T>`/`multiset<T>` | Insert/erase/find $O(log n)$ | Ordered sets, coordinate compression |
| `map<K,V>`/`multimap<K,V>` | Insert/erase/find $O(log n)$ | Ordered maps, frequency counts |
| `unordered_set<T>`/`unordered_multiset<T>` | Insert/erase/find $O(1)$ avg | Fast lookup, frequency counts |
| `unordered_map<K,V>`/`unordered_multimap<K,V>` | Insert/erase/find $O(1)$ avg | Fast maps, hash tables |
| `bitset<N>` | Bitwise ops $O(1)$, access $O(1)$ | Bitmask DP, subset problems |
| `string` | Access $O(1)$, concat $O(n)$ | Token parsing, hashing, string algorithms |
| `pair<A,B>`/`tuple<...>` | Structured grouping, lex compare | Edges, multi-value returns |

## Arrays
- `vector`, `array`, `queue`, `dequeue`, `stack`, `bitset<N>`
- talking about iterators
- talking about strings

# Specific Containers


## Heaps
- `priority_queue`

## Trees (Ordered Associative)
Based on Balanced BST.
- `set`
    * typical `set.insert()`, ``
    * we can only operate on iterators through `set.begin()`/`set.end()`, `next(iterator,steps)`
    * also `set.find(element)` gives back an iterator. Check if the element has been found via `iterator != set.end()`
    * to traverse use `for (auto it = set.begin(); it != set.end(); it++){ cout << *it; }`
    * since sets only store unique values `set.size()` gives back the count of distinct values
- `map`

## Hash Map (Unordered Associative)
- `unordered_set`, `unordered_map`

## Utilities
- `pair`, `tuple`, `optional`, `variant`


# Algorithm Design
## Problem Categories
* **Decision**: (True/False)
* **Search / Construct** (Valid Solution / Structure)
* **Counting** (Number of Solutions)
* **Enumeration** (All Solutions)
* **Optimization** (Best Value)
* **Approximation** (Near Optimal)
* **Interactive** (Answering Queries)

## Core Paradigms

### 1. Brute Force
Try **all possibilities** directly.
- Guaranteed correct if implemented correctly
- Almost always too slow in runtime

### 2. Greedy
Make **locally optimal** decisions, which *(hopefully)* also lead to **global optimum**.
- Fast and simple when valid
- Incorrect for many types of problems
- Requires justification through invariant or exchange argument

### 3. Divide & Conquer
Split problem into **disjoint** subproblems, solve each recursively, then merge results.
- Reduces complexity by splitting up search space

### 4. Dynamic Programming
Break a problem into **overlapping** subproblems, cache results and then reuse them.
- **Top-down**: recursion + memoization.  
- **Bottom-up**: iterative filling of a table
- Requires state definition and transitions.

### 5. Modeling & Structure
Rephrase the problem so known structures apply.
- Take datastructure and construct it in a fitting way
- Reduce problem to easier known problem
- Examples: Graphs, Union-Find, Fenwick, Compression

### 6. Sweep line and offline queries
**When to use**: Many queries on existence or threshold in a specific range $l,r$ needed
**Datastructures**: Event Bucketing

# Advanced Datastructures

## Monotone Stacks
Compute nearest constraint in $O(n)$ for each position.

Here `prevGreater` for storing index `j` of previous element `a[j] > a[i]`
```cpp
// prevGreater[i]: last j<i with a[j] > a[i], else -1
vector<int> prevGreater(int n, const vector<int>& a) {
    vector<int> st, L(n, -1);
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] <= a[i]) st.pop_back();
        L[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    return L;
}

// nextSmaller[i]: first j>i with a[j] < a[i], else n
vector<int> nextSmaller(int n, const vector<int>& a) {
    vector<int> st, R(n, n);
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        R[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }
    return R;
}
```

# Sorting & Searching
First you need to sort your container via
- `sort(vector.begin(), vector.end())` most basic **ASC** sort
- `sort(vector.begin(), vector.end(), greater<ll>());` most basic **DESC** sort

Then you can search for elements via
| Function | Returns | Meaning |
|----------|---------|-------------|
| `binary_search(first, last, val)` | **`true`** $\iff$ `val` exists in `[first, last)`. | 	Existence test in sorted range |
| `lower_bound(first, last, val)` | Iterator to **first element `≥ val`** (or `last` if none). | First element of the equal-or-greater range |
| `upper_bound(first, last, val)` | Iterator to **first element `> val`** (or `first` if none). | End of equal range |
| `equal_range(first, last, val)` | **Pair of iterators** `[lower_bound, upper_bound)`. | Range of elements equal to `val` |

If you want **Floor** (largest $\leq x$):
```cpp
auto it = A.upper_bound(x);
if (it == A.begin()) // implies there are no values <= x in A
else { --it; cout << *it; } // it is largest value <= x in A
```
If you want **Ceil** (smallest $\geq x$):
```cpp
auto it = A.lower_bound(x);
if (it == A.end()) // implies there are no values >= x in A
else { cout << *it; } // it is smallest value >= x in A
```

## Iterators
- `.front()` returns reference to first element
- `.begin()` returns iterator to first element (you want to use for iterations)

## BinarySearch
To implement you have to go through these steps:
1. **Monotonicity Check**: Is there a YES/NO question about value `m` which is also the same for all values `x > m` or `x < m`
2. **Search Space**: Define range $[l,r]$ of possible answers (what is the smallest, what is the largest)
3. **Shrink Search Space** via assigning new values to $l$ and $r$:


- Find **minimum**(*first*) value `x` such that `condition(x)` is *TRUE* (Lower Bound):
```cpp
ll ans=-1; // if no element with true for condition is found
ll l=0,r=n-1;
while (l <= r) {
    ll m = l+(r-l)/2;
    if (condition(m)) {
        ans = mid;
        r = m-1; // shrink space to [l, m-1]
    } else {
        l = m+1; // shrink space to [m+1, r]
    }
}
return ans;
```
- Find **maximum**(*last*) value `x` such that `condition(x)` is *TRUE* (Upper Bound):
```cpp
ll ans=-1; // if no element with true for condition is found
ll l=0,r=n-1;
while (l <= r) {
    ll m = l+(r-l)/2;
    if (condition(m)) {
        ans = mid;
        l = m+1; // shrink space to [m+1, r]
    } else {
        r = m-1; // shrink space to [l, m-1]
    }
}
return ans;
```
- Find **peak** value `x` in an array that increases and then decreases:
```cpp
while (l < r) {
    ll m = l+(r-l)/2;
    if (A[m] < A[m+1]) {
        l = m+1; // we are ascending - shrink space to [m+1, r]
    } else {
        r = m; // we are descending - shrink space to [l, m]
    }
}
return r;
```

## Prefix Sums
We want to find out the sum of a specific $[l,r)$ interval (subarray $a_l,\dots,a_{r-1}$) in our ($0$-based) array `A`. The naive approach would be to calculate it for each of our $q$ queries. This would lead to $O(n\cdot q)$ runtime.

The solution is **Prefix Sums**. We calculate on the fly for each element $i$ in the array, what the sum for interval $[0,i)$ is ($\sum_{j=0}^{i-1}a_j$) and assign that value to `prefix[i]=A[0]+ ... + A[i-1]`. Runtime is $O(n)$ for preprocessing and $O(1)$ per query. So $O(n+q)$ in total.

**Building**: `vector<ll> prefix(n+1,0)` with `prefix[0]=0` and then iterate with an index, e.g.  
`for (int i = 0; i < n; ++i) prefix[i+1] = prefix[i] + A[i];`

To then get the **value of interval** (subarray $a_l,\dots,a_{r-1}$) $[l,r)$ you simply compute the difference of prefixes $\sum_{j=l}^{r-1} a_j = \text{prefix}[r] - \text{prefix}[l]$.

In general an interval is *open*, so **exclusive** with `(` and *closed*, so **inclusive** with `]`.

So all intervals for a **$0$-based** array are defined as:
- $[l,r)$ => `sum = prefix[r] - prefix[l]` **(recommended)** (non empty $\iff r > l$)
- $[l,r]$ => `sum = prefix[r+1] - prefix[l]` (non empty $\iff r \geq l$; requires $r < n$)
- $(l,r)$ => `sum = prefix[r] - prefix[l+1]` (non empty $\iff r > l+1$)
- $(l,r]$ => `sum = prefix[r+1] - prefix[l+1]` (non empty $\iff r > l$)


### Usecases
- **Count amount** of subarrays with **specific property** => use map/vector of counts
    * *Subarrays which `sum==x`*: keep map `cnt[pref]`, scan `pref+=a[i]`, results in `res+=cnt[pref-x]` and `cnt[pref]++`
    * *Subarrays which `sum%x==0`*: bucket by remaining value `r=(pref % x + x) % x`, results in `res+=seen[r]` and `seen[r]++`
- Max length subarray => store earliest+latest index per key
- divisibility, modulo

## Prefix aggregates for range existence

exists a witness inside [l, r] that the property needed is not met

# Graphs
## Data Structures
### Adjacency Matrix
- **Description**: $n \times n$ Matrix. $A_{i,j}=1$ means there is an edge from vertex $i$ to $j$
- **Space**: $O(n^2)$
- **Count Neighbours**: $O(n)$
- **Test Edge**: $O(1)$
- **Implementation**: ``vector<vector<bool>> A(n, vector<bool>(n, false))``

### Adjacency List
- **Description**: List with $n$ Entries, each having an array containing all vertices it's connected to.
- **Space**: $O(n+m)$
- **Count Neighbours**: $O(|\text{neighbours}|)$
- **Test Edge**: $O(|\text{neighbours}|)$
- **Implementation**: ``vector<vector<int>> adjlist``, for *weighted* ``vector<vector<pair<int,ll>>> adj``

### Edge List
- **Description**: List of all Edges displayed as a pair of the connected vertices
- **Space**: $O(m)$
- **Count Neighbours**: $O(m)$
- **Test Edge**: $O(m)$
- **Implementation**: ``vector<pair<int,int>> edges``

## Graph Traversal

### Breadth-First Search (BFS)
- **Purpose**: Find shortest paths in unweighted Graph (and discover connectivity by layers)
- **Description**: Level‐by‐level (breadth‐first) exploration from the start vertex $s$
- **Runtime**: $O(n+m)$
- **Input**: Adjacency List `vector<vector<int>> &adjlist`, Starting vertex `s`
- **Output**:
- **Code**:
```cpp
vector<int> dist(n, -1), parent(n, -1);
queue<int> q;

dist[s] = 0;
q.push(s);

while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
        if (dist[v] == -1) { // Unvisited
            dist[v] = dist[u] + 1;
            parent[v] = u; // path reconstruction
            q.push(v);
        }
    }
}
```

### Depth-First Search (DFS)
- **Purpose**: Detect connectivity, reachability, cycles. Construct Paths. Perform topological sorting. Solve *backtracking* problems.
- **Description**: Explores Graph greedy from starting vertex $s$
- **Runtime**: $O(n+m)$
- **Input**: Adjacency List `vector<vector<int>> &adjlist`, Starting vertex `s`
- **Output**: DFS Tree
- **Code**:
```cpp
vector<bool> visited(n, false);
vector<int> parent(n, -1);
auto dfs = [&](auto &&self, int u) -> void {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            self(self, v);
        }
    }
};

dfs(dfs, s);
```
to get the output:
```cpp
for (int w = 0; w < n; ++w) {
    if (parent[w] != -1)
        cout << parent[w] << " --> " << w << "\n";
}
```

### Connectivity
Graph $G$ is **connected** $\iff$ there is a path $v_i \to \dots \to v_j$ between any distinct nodes $v_i,v_j\in V$.

So we can just start at any node and test if we can reach all other nodes (for example with DFS).

### Cycles
Graph $G$ **contains a cycle** $\iff$ during traversal we find a neighbour node which has already been visited (except prev node of path) $\iff$ there exists a component $G'\subseteq G$ that doesn't exactly contain $|V'|-1$ edges

### Bipartite
Graph $G$ is **bipartite** $\iff$ there exists a way to color all nodes $v \in V$ with two distinct colors $c_1,c_2$, but without any adjacent nodes having the same color $\forall v' \in N(v): c(v') \neq c(v)$.

## Shortest Path

### Dijkstra
- **Purpose**: Compute shortest paths from a single source to every other vertex in a non-negatively weighted graph
- **Description**: Use a min-heap to repeatedly extract the closest vertex and relax its outgoing edges until all shortest distances from the source are determined.
- **Runtime**: $O(m \log n)$
- **Input**: Adjacency List `vector<vector<pair<int,int>>> &adj`, Starting vertex `s`
- **Output**: Vector with shortest distance from $s$ to every vertex $v$ `vector<ll> dist(n)`, optionally also `vector<int> prev(n)` for the reconstructed path
- **Code**:
```cpp
const ll INF = 1e18;
vector<ll> dist(n, INF);
priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq; // Min-priority queue storing {distance, node}

dist[s] = 0;
pq.push({0, s});

while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue; // Skip outdated states
    for (auto [v, w] : adj[u]) { // w is weight
        if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }
}
```
All-Pairs Helper, efficient for sparse graphs: $O(N * M * log(N))$ to pay up-front cost.
```cpp
vector<vector<ll>> buildAllPairs(const vector<vector<pair<int,int>>>& adj) {
    int n = adj.size();
    vector<vector<ll>> D(n); 
    for (int s = 0; s < n; ++s) {
        D[s] = dijkstra(adj, s);
    }
    return D;
}
```

### Bellman-Ford
- **Purpose**: Shortest paths from source $s$ in graph with negative weights (detects negative cycles).
- **Runtime**: $O(n\cdot m)$
- **Input**: Edge List `struct Edge { int u, v, w; }`
- **Code**:
```cpp
struct Edge { int u, v, w; };
vector<Edge> edges;
vector<ll> dist(n, INF);

dist[s] = 0;
for (int i = 0; i < n - 1; ++i) { // Relax all edges n-1 times
    for (auto& e : edges) {
        if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v])
            dist[e.v] = dist[e.u] + e.w;
    }
}
for (auto& e : edges) { // Run one more time to detect negative cycle
    if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
        cout << "Negative Cycle Detected!" << endl;
        dist[e.v] = -INF; // Mark as arbitrarily small
    }
}
```

### Floyd-Warshall
- **Purpose**: Find all shortest Paths in a (weighted) Graph
- **Description**: Iterates over all vertex combinations
- **Runtime**: $O(n^3)$
- **Input**: Adjacency Matrix
- **Output**: 2D Array `mat` where `mat[i][j]`= shortest distance from vertex $i$ to $j$
- **Code**:
```cpp
for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) { // Check if path through k is shorter
            if (d[i][k] < INF && d[k][j] < INF) // check to avoid overflow
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
    }
}
```

# Trees
**Tree** = ***connected***, ***acyclic*** graph with $|V|=n$ **nodes** and $|E|=n-1$ **edges**.
- *removing any edge* splits it into **two components**
- *Adding any edge* creates a **cycle**
- **Leaf** = node $v$ with $\deg(v)=1$
- **Root** = node $r$ with no parent
- **Children** = lower neighbors of a node
- **Parent** = upper neighbor of a node
- *each node acts as root of a **subtree***

## Tree Traversal




# Dynamic Programming

## Knapsack
**Given**:
- $G=\{1, \dots, n\}$ **Objects** ($1 \leq |G| \leq 10^3$)
- $C \in \mathbb{N}$ **Capacity** ($1 \leq C \leq 10^4$)
- $v: G \to \mathbb{N}$ **Value** ($1 \leq v_i \leq 10^9$)
- $w: G \to \mathbb{N}$ **Weight** ($1 \leq w_i \leq 10^9$)

**Question**:
- What is the **max total value of unique objects**, which total weight is smaller than the capacity?

Sub-Solution:
- $F_{i,j}$ is max value of first $i$ objects with $j$ capacity
- We are looking for $F_{n,C}$
- Define **Base Cases**: $\forall j: F_{0,j}=0$ and $\forall i: F_{i,0}=0$
- Define **Recurrence**: For $i,j \geq 1$ is
$$
F_{i,j} =
\begin{cases}
F_{i-1,j} & w_i > j\\[4pt]
\max\bigl(F_{i-1,j},\; F_{i-1,\,j-w_i}+v_i\bigr) & \text{else}
\end{cases}
$$

DP Solution:
```cpp
for(int64_t i = 1; i <= n; ++i)
    for(int64_t j = 1; j <= C; ++j) {
        f[i][j] = f[i-1][j];
        if (j >= w[i])
            f[i][j] = max(f[i - 1][j], f[i-1][j-w[i]] + v[i]);
}
```

## Coins

## Longest Subsequence

# Strings

# Geometry
## Basics
- **Never use** `float`
- Prefer `long long` for exact integer geometry
- If you *absolutely need* non-integral values, use `long double`



Treat any $|x|<EPS$ as zero:
```cpp
long long EPS = 1e-9;
int sgn(long double x) {
    if (x >  EPS) return +1;   // significantly positive
    if (x < -EPS) return -1;   // significantly negative
    return 0;                  // close enough to zero
}
```
Useful for comparisons with tolerance


## Points & Vectors
**Point** (**Vector**)
most robust:
```cpp
struct P { 
    long long x, y; 
    P operator+(P o)const{return {x+o.x,y+o.y};}
    P operator-(P o)const{return {x-o.x,y-o.y};}
    P operator*(double k)const{return {x*k,y*k};}
};
```

via this all operations are already available:
```cpp
using P = complex<long double>;
```
where
```cpp
P p(x,y);
long double x = p.real(), y = p.imag();
```

**Squared Distance**
```cpp
long long sqdist(P a, P b) {

}
```

**Dot Product** (scalar product)
```cpp
double dot(P a,P b){ 
    return a.x*b.x + a.y*b.y; 
}
```

**Cross Product** (vector product)
```cpp
long long cross(P a, P b, P c){
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}
```

**Counter Clockwise**
```cpp
int ccw(P a, P b, P c){ 
    return sgn(cross(b-a,c-a)); 
}
```
- $>0$: left turn (counter clockwise)
- $=0$: collinear
- $<0$: right turn (clockwise)

## Primitives

**Segment**
two endpoints

**Line**
two different points

Projection of point onto line

reflection across line

Distance point→line and point→segment

## Intersection Tests
### Segment-Segment
- **Input**: Segments `ab` and `cd`
- **Task**: Decide if `ab` and `cd` cut each other
- **Observation**: If they cut, `c` and `d` have to be on different sites of `ab` (and other way around)
```cpp
bool intersect (P a, P b, P c, P d) {
    if (ccw(a, b, c) == 0 && ccw(a, b, d) == 0) {
        if (sqdist(a, b) < sqdist(c, d)) {
            swap(a, c), swap(b, d);
        } 
        int64_t dab = sqdist(a, b);
        return (sqdist(a, c) <= dab && sqdist(b, c) <= dab) ||
                (sqdist(a, d) <= dab && sqdist(b, d) <= dab);
    }
    return ccw(a, b, c) * ccw(a, b, d) <= 0 &&
            ccw(c, d, a) * ccw(c, d, b) <= 0;
}
```

### Line-Line

...

## Polygons

Area & perimeter

Point-in-polygon (winding vs. ray-cast)

Convex vs. non-convex


### Convex Hull
- **Input**: Set of points `vector <pt> &pts`
- **Task**: Find smallest konvex polygon which holds `pts`
- **Observation**: Counter clockwise only Linksknicke
- **Andrews Algorithm**: Calculate upper and lower hull seperately by sorting each lexicographically, adding the next point and deleting all previous points which create a Rechtsknick
```cpp
vector<P> hull(vector<P> &pts) {
    sort(pts.begin(), pts.end());
    auto half_hull = [](auto begin, auto end) {
        vector<P> res(end - begin); // max size of hull
        int64_t k = 0;               // real size of hull
        for (auto it = begin; it != end; ++it) {
            while (k >= 2 && ccw(res[k - 2], res[k - 1], *it) <= 0) --k;
            res[k++] = *it;
        }
        res.resize(k);
        return res;
    };
    vector<P> lower = half_hull(pts.begin(), pts.end());   // forward
    vector<P> upper = half_hull(pts.rbegin(), pts.rend()); // backwards
    if (lower.size() == 1) { // edge case: single point
        return lower;
    }
    lower.insert(lower.end(), next(upper.begin()), prev(upper.end()));
    return lower;
}
```

## Closest Pair of Points
- **Input**: Set of points `vector <pt> &pts`
- **Task**: Find the two closest points `{p1, p2}` 
- **Process**: Iterate over the set, updating the *shortest currently known distance* `d` by observing **sweeps** of *width* `d` and *height* `d*2` if any of them are closer than `d`
```cpp
pair<P, P> closest_pair(vector<P> &pts)
{
    sort(pts.begin(), pts.end(), comp_x);
    set<P, bool (*)(P, P)> sweep({*pts.begin()}, comp_y); 
    long double opt = INF; 
    P p1, p2;

    for (size_t left = 0, right = 1; right < pts.size(); ++right)
    {
        while (pts[right].x - pts[left].x >= opt) {
            sweep.erase(pts[left++]);
        }
        auto lower = sweep.lower_bound(P{-INF, pts[right].y - opt});
        auto upper = sweep.upper_bound(P{-INF, pts[right].y + opt});
        for (auto it = lower; it != upper; ++it) {
            long double d = dist(pts[right], *it);
            if (d < opt) {
                opt = d;
                p1 = *it;
                p2 = pts[right];
            }
            sweep.insert(pts[right]);
        }
    }
    return {p1, p2};
}
```

## Circle 
```cpp
struct circ { P x; long long r; };
```

Circle–point tests, tangents from a point

Line–circle intersection

Circle–circle intersection & common tangents

Power of a point, radical axis

## Triangle

Area by cross product

Incenter, circumcenter, centroid, orthocenter

## Advanced
Voronoi diagram
...

# Mathematics