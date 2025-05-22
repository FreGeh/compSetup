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