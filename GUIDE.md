# Practical
## Reading Input
- `cin >>` reads whole string till space
- `cin.get(c)` reads `char c`, also spaces and `\n`
- `vector<char> S(tmp.begin(), tmp.end())` seperates string into char vector

### Example for $n$ numbers
```cpp
int n;
cin >> n;
vector<int> N(n);
for (int &x: N) cin >> x;
```

## Output
- `(boolFunction() ? "true" : "false")` to automatically output a string depending on the bool value

## Math Tricks
- Round Up in fractions, use `a+b-1/b` instead of `a/b`.

## STDL Tricks
- To Check if Vector `S` is Palindrome: `equal(S.begin(), S.begin() + S.size() / 2, S.rbegin());`

# Theory
## Strategies
### Full Search
Search through entire solution space for correct one.
- easy, correct
- too slow

### Backtracking
1. Filter: Generate all possible candidates (raw recursion - validation at end)
2. Generator: Generate only valid candidates (recursion with logic at every step)
3. Pruning: Try to recognize invalid solutions during generation and only continue working on possible valid ones

### Greedy
Local optimal decisions need to be globally optimal, since it doesn't take back previous decisions. Otherwise it's incorrect.
- efficient
- incorrect for many types of problems

### Binary Search
Search for biggest element in sorted list. Split up search space each round.
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


### Guess Solution
- Solution doesn't work => smaller won't either
- Solution works => bigger will too

### DP

## Algorithms

## Data Types

## Data Structures

# Random

## Git
- `git add *.md` so I don't add changed simple.cpp, etc.
- `git wipe` macro to reset repo to github status, the setup in `~/.gitconfig` is:
```
[alias]
  wipe = "!f() { \
      git fetch --all --prune && \
      git reset --hard @{u} && \
      git clean -fdx; \
    }; f"
```