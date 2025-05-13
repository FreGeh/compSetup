Here I write down anything I learn:

# Reading Input
`cin >>` reads whole string till space
`cin.get(c)` reads `char c`, also spaces

for n numbers:
``int n;
    cin >> n;
    vector<int> N(n);
    for (int &x : N) {
        cin >> x;
    }
``

# Math Tricks
To round up in fractions, use `a+b-1/b` instead of `a/b`.

# Strategies
## Full Search
Search through entire solution space for correct one.
- easy, correct
- too slow

## Backtracking
1. Filter: Generate all possible candidates (raw recursion - validation at end)
2. Generator: Generate only valid candidates (recursion with logic at every step)
3. Pruning: Try to recognize invalid solutions during generation and only continue working on possible valid ones

## Greedy
Local optimal decisions need to be globally optimal, since it doesn't take back previous decisions. Otherwise it's incorrect.
- efficient
- incorrect for many types of problems

## Binary Search
Search for biggest element in sorted list. Split up search space each round.

## Guess Solution
- Solution doesn't work => smaller won't either
- Solution works => bigger will too

## DP

# Algorithms

# Data Types

# Data Structures
