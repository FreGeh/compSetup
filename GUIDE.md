# Practical
## Reading Input
- `cin >>` reads whole string till space
- `cin.get(c)` reads `char c`, also spaces and `\n`
- `vector<char> S(tmp.begin(), tmp.end())` seperates string into char vector

# Workflow
1. `g++ -std=c++20 -O2 -Wall program.cpp -o program`
2. `./program < input.txt`

# Basics C++

## Output
- `(boolFunction() ? "true" : "false")` to automatically output a string depending on the bool value

## Math Tricks
- Round Up in fractions, use `a+b-1/b` instead of `a/b`.

## STDL Tricks
- To Check if Vector `S` is Palindrome: `equal(S.begin(), S.begin() + S.size() / 2, S.rbegin());`

## Input/Output
`cin >>` reads whole string till space
`cin.get(c)` reads `char c`, also spaces

for $n$ numbers:
```cpp
int n;
cin >> n;
vector<int> N(n);
for (int &x : N) {
    cin >> x;
}
```

## Data Types

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
- **BinarySearch**: Search for biggest element in sorted list. Split up search space each round.
```pseudo
function binarySearch(A, target)
    low  ← 0
    high ← length(A) − 1
    while low ≤ high do
        mid ← low + (high − low) / 2      // avoids overflow
        if A[mid] = target then
            return mid                     // found
        else if A[mid] < target then
            low ← mid + 1                  // search right half
        else
            high ← mid − 1                 // search left half
    return −1                              // not found
```

## Backtracking
1. **Filter**: Generate all possible candidates (raw recursion - validation at end)
2. **Generator**: Generate only valid candidates (recursion with logic at every step)
3. **Pruning**: Try to recognize invalid solutions during generation and only continue working on possible valid ones

## Parametric Search
- Solution $x$ doesn't work => smaller $<x$ won't either
- Solution $x$ works => bigger $>x$ will too

*(the reverse is also possible)*
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
- Define **Recurrence**: For $i,j \geq 1$ is $F_{i,j}=$
    - $F_{i-1,j}$ if object $i$ doensn't get added
    - $F_{i-1,j-w_i+v_i}$ if object $i$ gets added


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

## Dijkstra
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

## Geometry

# Data Structures

# Math
## Tricks
To round up in fractions, use `a+b-1/b` instead of `a/b`.

# Complexity
## Output
- `(boolFunction() ? "true" : "false")` to automatically output a string depending on the bool value

## Math Tricks
- Round Up in fractions, use `a+b-1/b` instead of `a/b`.

## STDL Tricks
- To Check if Vector `S` is Palindrome: `equal(S.begin(), S.begin() + S.size() / 2, S.rbegin());`