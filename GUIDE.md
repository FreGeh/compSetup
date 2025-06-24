# Practical

## Workflow
1. `g++ -std=c++20 -O2 -Wall program.cpp -o program`
2. `./program < input.txt` 

## Fast I/O template

```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);
```

## Constraints
| Typical technique                               | Time complexity                       | Safe max $n$ (≈ 2 s in C++) |
| ----------------------------------------------- | ------------------------------------- | --------------------------- |
| Linear scan, two-pointer, cumulative sums       | $\mathcal O(n)$                       | $\sim 10^{8}$               |
| Sorting (merge sort, quicksort, heapsort)       | $\mathcal O(n \log n)$                | $\sim 10^{6}$               |
| Counting / radix sort (fixed word size)         | $\mathcal O(n)$                       | $\sim 10^{7}$               |
| BFS / DFS on graph $(n+m)$                      | $\mathcal O(n+m)$                     | $n,m \le 2\cdot 10^{5}$   |
| Dijkstra / Prim (binary heap)                   | $\mathcal O(m \log n)$                | $n,m \le 2\cdot 10^{5}$   |
| Segment tree / Fenwick tree (updates + queries) | $\mathcal O\!\bigl((n+q)\log n\bigr)$ | $n,q \le 2\cdot 10^{5}$   |
| Mo’s algorithm, block decomposition             | $\mathcal O(n\sqrt n)$                | $\sim 10^{5}$               |
| DP on pairs, prefix tables, double loop         | $\mathcal O(n^{2})$                   | $\sim 10^{4}$               |
| Floyd–Warshall, cubic DP, matrix multiplication | $\mathcal O(n^{3})$                   | $\sim 500$                  |
| Bitmask DP / enumerate all subsets              | $\mathcal O(n\,2^{n})$                | $n \le 22$                  |
| Backtracking all permutations                   | $\mathcal O(n!)$                      | $n \le 11$                  |


# Basics C++

## Input
- `cin >>` reads whole string till space
- `cin.get(c)` reads `char c`, also spaces and `\n`
- `getline(cin, s)` reads whole line as `string s`
- `vector<char> S(tmp.begin(), tmp.end())` seperates string into char vector

for $n$ numbers:
```cpp
int n;
cin >> n;
vector<int> A(n);
for (int &x : A) {
    cin >> x;
}
```

## Output
- `cout <<` standard
- `(bool ? "true" : "false")` to output a value depending on the bool value

## Math Tricks
- Round Up in fractions, use `a+b-1/b` instead of `a/b`.

## STL Tricks
```cpp
iota(v.begin(), v.end(), 0);          // 0,1,2,...
accumulate(v.begin(), v.end(), 0LL); // sum
sort(v.begin(), v.end(), greater<>()); // descending
equal(v.begin(), v.begin()+n/2, v.rbegin()); // palindrome
```


## Data Types
| Type                 | Size / Range                                                 | Notable properties                                  |
| -------------------- | ------------------------------------------------------------ | --------------------------------------------------- |
| `int`                | $4\text{ B},\;[-2^{31},\,2^{31}\!-\!1]$                      | fastest arithmetic, default loop index              |
| `long long`          | $8\text{ B},\;\approx[-9{\times}10^{18},\,9{\times}10^{18}]$ | 64-bit signed, safe for most sums/products          |
| `unsigned int`       | $4\text{ B},\;[0,\,2^{32}\!-\!1]$                            | wrap-around mod $2^{32}$; bit masks                 |
| `unsigned long long` | $8\text{ B},\;[0,\,2^{64}\!-\!1]$                            | 64-bit unsigned, modular hashes                     |
| `double`             | $8\text{ B},\;\sim15$ decimal digits                         | hardware FPU; geometry, probabilistic DP            |
| `long double` (GCC)  | $16\text{ B},\;\sim18$ digits                                | extra precision for numeric analysis                |
| `char`               | $1\text{ B},\;[0,255]$                                       | tiny integer; ASCII grids, bit tricks               |
| `bool`               | $1\text{ B}$ (bit-packed in `vector<bool>`)                  | logical flags, visited arrays                       |
| `size_t`             | $8\text{ B},\;[0,\,2^{64}\!-\!1]$                            | unsigned type returned by `sizeof`, container sizes |

## Data Structures
| Container / Helper                        | Key operations                                 | Typical contest use                                  |
| ----------------------------------------- | ---------------------------------------------- | ---------------------------------------------------- |
| `vector<T>`                               | `push_back`, index $\mathcal O(1)$ (amortised) | dynamic arrays, graphs, DP tables                    |
| `array<T,N>`                              | fixed size, index $\mathcal O(1)$              | small static DP or geometry structs                  |
| `deque<T>`                                | `push_front/back` $\mathcal O(1)$              | sliding-window min/max, 0-1 BFS                      |
| `stack<T>`                                | LIFO `push/pop` $\mathcal O(1)$                | DFS, parentheses checker                             |
| `queue<T>`                                | FIFO `push/pop` $\mathcal O(1)$                | standard BFS                                         |
| `priority_queue<T>`                       | `push/pop` $\mathcal O(\log n)$                | Dijkstra, K-largest elements                         |
| `set<T>` / `map<K,V>`                     | insert, erase, find $\mathcal O(\log n)$       | sweep-line, order statistics, coordinate compression |
| `unordered_set<T>` / `unordered_map<K,V>` | avg. insert/find $\mathcal O(1)$               | frequency counts, fast lookup (watch hacks)          |
| `bitset<N>`                               | bit ops in $\mathcal O(N/64)$                  | subset DP up to $10^{4}$ bits                        |
| `string`                                  | contiguous bytes; length $\mathcal O(1)$       | token parsing, hashing                               |
| `pair<A,B>` / `tuple<…>`                  | lexicographic compare, `tie`                   | edges, multi-value returns                           |
| `segment tree` (`vector`)                 | update/query $\mathcal O(\log n)$              | range sums, max, lazy propagation                    |
| `Fenwick tree` (`vector`)                 | prefix sum/update $\mathcal O(\log n)$         | inversion count, 1-D BIT                             |
| `priority_queue<pair<ll,int>>`            | —                                              | Dijkstra with distances                              |


# Strategies
## Brute Force
Search through entire solution space for correct one.
- easy, correct
- too slow

## Greedy
Local optimal decisions need to be globally optimal, since it doesn't take back previous decisions. Otherwise it's incorrect.
- efficient
- incorrect for many types of problems

## Divide & Conquer
* **Idea:** break problem into $k$ sub-instances, solve recursively, merge.
* **Classic uses:**

  * Merge sort, quicksort
  * Closest pair of points $O(n\log n)$
  * “Divide & Conquer DP” / “CDQ” optimisation $O(n\log n)$

## Backtracking
1. **Filter**: Generate all possible candidates (raw recursion - validation at end)
2. **Generator**: Generate only valid candidates (recursion with logic at every step)
3. **Pruning**: Try to recognize invalid solutions during generation and only continue working on possible valid ones

## Parametric Search
- Solution $x$ doesn't work => smaller $<x$ won't either
- Solution $x$ works => bigger $>x$ will too

*(the reverse is also possible)*

Implement **predicate** `can(x)`; binary-search smallest/largest `x` for quick checks.

## Dynamic Programming
1. Segment hard problem into easier problems 
2. Solve each problem independently
3. Bring the solutions together to solve the hard problem

### Bottom Up
1. Define Sequence of which problems get solved
2. Save sub-solutions
3. Solve bigger problem with sub-solutions

### Top-Down
1. Segment hard problem into easier problems 
2. Define Recursion Formula
3. Solution Known => Use it
3. Solution Unknown => Solve and then save it, so you dont have to do it again (**Memoisation**)

# Problems

## Decision: True/False

## Search (Valid Solution)

## Construct (Valid Structure)

## Counting (Number of Solutions)
**Strategies**: DP, 

## Enumeration (All Solutions)

## Approximation (Near Optimal)

## Optimization (Best Value)
**Strategies**: DP, 

### Knapsack
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


```cpp
for(int64_t i = 1; i <= n; ++i)
    for(int64_t j = 1; j <= C; ++j) {
        f[i][j] = f[i-1][j];
        if (j >= w[i])
    f[i][j] = max(f[i - 1][j], f[i-1][j-w[i]] + v[i]);
}
```

### Longest Subsequence
**Given**:
- 

## Interactive (Queries)

# Important Algorithms

## Sort & Search
### BinarySearch
Search for biggest element in sorted list. Split up search space each round.
```pseudo
function binarySearch(A, target)
    low  ← 0
    high ← |A| − 1
    while low ≤ high do
        mid ← low + (high − low) / 2      // overflow-safe
        if A[mid] == target then return mid
        if A[mid]  < target then low  ← mid + 1   // go right
        else                   high ← mid − 1    // go left
    return −1                                   // not in A
```
In C++ there are:
| Function                          | Meaning                                                    | Typical use                                  |
| --------------------------------- | ---------------------------------------------------------- | -------------------------------------------- |
| `binary_search(first, last, val)` | Returns **`true`** iff `val` exists in `[first, last)`.    | Quick membership test.                       |
| `lower_bound(first, last, val)`   | Iterator to **first element `≥ val`** (or `last` if none). | Insert position that keeps the range sorted. |
| `upper_bound(first, last, val)`   | Iterator to **first element `> val`** (strictly greater).  | Right end of the run of equal keys.          |
| `equal_range(first, last, val)`   | Returns `{lower_bound, upper_bound}`.                      | Span of all elements equal to `val`.         |


## Graphs
### Data Structures
#### Adjacency Matrice
- **Description**: $n \times n$ Matrice. $A_{i,j}=1$ means there is an edge from vertice $i$ to $j$
- **Space**: $O(n^2)$
- **Count Neighbours**: $O(n)$
- **Test Edge**: $O(1)$
- **Implementation**: ``vector<vector<bool>> A(n, vector<bool>(n, false))``

#### Adjacency List
- **Description**: List with $n$ Entries, each having an array containing all vertices it's connected to.
- **Space**: $O(n+m)$
- **Count Neighbours**: $O(|\text{neighbours}|)$
- **Test Edge**: $O(|\text{neighbours}|)$
- **Implementation**: ``vector<vector<int>> adjlist``, for *weighted* ``vector<vector<pair<int,ll>>> adj``

#### Edge List
- **Description**: List of all Edges displayed as a pair of the connected vertices
- **Space**: $O(m)$
- **Count Neighbours**: $O(m)$
- **Test Edge**: $O(m)$
- **Implementation**: ``vector<pair<int,int>> edges``

### BFS
- **Purpose**: Find shortest paths in unweighted Graph (and discover connectivity by layers)
- **Description**: Level‐by‐level (breadth‐first) exploration from the start vertex $s$
- **Runtime**: $O(n+m)$
- **Input**: Adjacency List, Starting Vertice $s$
- **Output**: 
- **Code**:
```cpp
int s = 42; // Startknoten
vector<vector<int>> &adjlist;
int n = adjlist.size();

queue<int> q;
q.push(s);

vector<int> dist(n, INF), parent(n, -1);
dist[s] = 0;
parent[s] = -1;

while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (int w : adjlist[v]) {
        if (dist[w] == INF) {
            dist[w] = dist[v] + 1;
            parent[w] = v;
            q.push(w);
        }
    }
}
```
and for the output:
``` cpp
for (int w = 0; w < n; ++w) {
    if (parent[w] != -1)
        cout << parent[w] << " --> " << w 
             << "  (dist=" << dist[w] << ")\n";
}
```

### DFS
- **Purpose**: Detect connectivity, reachability, cycles. Construct Paths. Perform topological sorting. Solve *backtracking* problems.
- **Description**: Explores Graph greedy from starting vertice $s$
- **Runtime**: $O(n+m)$
- **Input**: Adjacency List, Starting Vertice
- **Output**: DFS Tree
- **Code**:
```cpp
void visit(int v, vector<bool> &visited, vector<int> &parent) {
    visited[v] = true;
    for (int w : adjlist[v]) {
        if (!visited[w]) {
            parent[w] = v;
            visit(w, visited, parent);
        }
    }
}
```
to kick of the search and get the output:
```cpp
vector<vector<int>> &adjlist;
// n = Anzahl Knoten
vector<bool> visited(n, false);
vector<int>  parent(n, -1);
visit(s, visited, parent); // s = Startknoten

// get DFS tree
for (int w = 0; w < n; ++w) {
  if (parent[w] != -1)
    cout << parent[w] << " --> " << w << "\n";
}
```

### Floyd-Warshall
- **Purpose**: Find all shortest Paths in a (weighted) Graph
- **Description**: Iterates over all vertice combinations
- **Runtime**: $O(n^3)$
- **Input**: Adjacency Matrice 
- **Output**: 2D Array with shortest distance from vertice $i$ to $j$
- **Code**:
```cpp
// Initialisierung: mat [i][j] = Laenge / infty
for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (mat[i][k] + mat[k][j] < mat[i][j]) {
                mat[i][j] = mat[i][k] + mat[k][j];
            }
        }
    }
}
// Ergebnis: mat [i][j] = Distanz von i nach j .
```

### Dijkstra
- **Purpose**: Compute shortest paths from a single source to every other vertex in a non-negatively weighted graph
- **Description**: Use a min-heap to repeatedly extract the closest vertex and relax its outgoing edges until all shortest distances from the source are determined.
- **Runtime**: $O(m \log n)$
- **Input**: Adjacency List ``, Starting Vertice $s$
- **Output**: Vector with shortest distance from $s$ to every vertex $v$ `vector<ll> dist(n)`, optionally also `vector<int> prev(n)` for the reconstructed path
- **Code**:
```pseudo
function Dijkstra(graph, source):
    # Initialization
    for each vertex v in graph:
        dist[v] ← ∞
        prev[v] ← UNDEFINED
    dist[source] ← 0

    # Min-heap of (distance, vertex)
    Q ← empty priority queue
    Q.insert((0, source))

    # Main loop
    while Q is not empty:
        (d, u) ← Q.extract_min()
        if d > dist[u]:
            continue       # stale entry

        for each edge (u → v) with weight w in graph.adj[u]:
            alt ← dist[u] + w
            if alt < dist[v]:
                dist[v] ← alt
                prev[v] ← u
                Q.insert((alt, v))

    return dist, prev
```

When you have many queries on the same graph, pay the $O(n \cdot m \cdot log(n))$ “up‐front” cost:

```pseudo
function BuildLookupTable(graph):
    n ← graph.number_of_vertices
    create matrix dist[n][n], fill all with ∞

    for s in 0 … n−1:
        dist[s][s] ← 0
        (d_s, _) ← Dijkstra(graph, s)
        for v in 0 … n−1:
            dist[s][v] ← d_s[v]

    return dist
```
Then each query for distance from $a$ to $b$ is just:
```pseudo
ans ← dist[a][b]
if ans == ∞:
    print "not reachable"
else:
    print ans
```

## Strings
| Technique        | Solves                                                                    | Core idea                                                                                                                                          | Time                        |
| ---------------- | --------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------ | --------------------------- |
| **KMP**          | Find a single pattern `P` (`m`) inside text `T` (`n`)                             | Build `pi[]` (longest proper border of each prefix). While scanning `T`, on mismatch jump to `pi[k-1]` instead of restarting. Implement with `vector<int> pi(m);`. | `O(n + m)`                  |
| **Z-algorithm**  | Get, for every position, the longest prefix starting there (runs, pattern search) | Maintain current match box `[l,r]` equal to the prefix; extend each new index using that box. One forward pass filling `vector<int> z(n);`.                        | `O(n)`                      |
| **Rolling hash** | Constant-time substring compare, sliding window, duplicate detection              | Store prefix hashes `H[i]` and powers `pow[i]`; hash of `[l,r]` is `H[r+1] − H[l]·pow[len]` mod `M`. Use two moduli to dodge collisions.                           | Build `O(n)`, query `O(1)`  |
| **Aho–Corasick** | Locate **many** patterns (total length `L`) in a single text (`n`)                | Insert patterns into a trie; BFS builds failure links (KMP on the trie). One linear scan over text follows `fail`/`next` edges and reports matches.                | Build `O(L)`, search `O(n)` |


## Geometry
```cpp
struct P{ long long x,y; };
long long cross(P a,P b,P c){
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}
```

* `cross>0` left turn, `<0` right turn, `=0` collinear.
* Distance squared `dsq = (dx*dx + dy*dy)` avoids `sqrt`.