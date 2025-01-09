# Table of Contents
- [Environment Setup](#environment-setup)
  - [WSL Setup (Windows Users)](#wsl-setup-windows-users)
    - [Optional: Rename Instance](#optional-rename-instance)
  - [Ubuntu Setup (Everyone)](#ubuntu-setup-everyone)
- [Solve a Problem on Codeforces](#solve-a-problem-on-codeforces)
  - [1. Choose a Problem](#1-choose-a-problem)
  - [2. Solve the Problem](#2-solve-the-problem)
  - [3. Compile and Test Locally](#3-compile-and-test-locally)
  - [4. Submit Your Solution](#4-submit-your-solution)
- [Explanations](#explanations)
  - [program.cpp](#programcpp)
    - [Head](#head)
    - [Body](#body)
  - [debug.h](#debugh)
- [Commandline Usage](#commandline-usage)
  - [Compiling](#compiling)
  - [Input and Output](#input-and-output)
- [Where to Go Next](#where-to-go-next)

# Environment Setup

## WSL Setup (Windows Users)
This is for **Windows** Users; **Linux users can skip this**.

Since platforms like **Codeforces** and local contests like ICPC run on **Linux-based OS**, we use **WSL** with **Ubuntu** to match that **official environment** (https://docs.icpc.global/worldfinals-programming-environment/). It's simpler than using Windows tools and doesn't affect speed.

1. Right-click the **Start Menu** -> PowerShell/Terminal (**Admin**).
2. Type `wsl --install`.
3. **Restart** your PC.
4. **Launch Ubuntu** from the Start Menu and set up your user.

### Optional: Rename Instance
If you already have WSL installed or plan to have multiple instances, organizing them helps.

1. **Open** a new PowerShell/Terminal (Admin).
2. Install an **additional instance**: `wsl --install -d Ubuntu-24.04`.
3. Create a **folder** for new WSL instances: `mkdir C:\WSL`.
4. **Export** the instance: `wsl --export Ubuntu-24.04 C:\WSL\UbuntuBackup.tar`.
5. **Unregister** the instance: `wsl --unregister Ubuntu-24.04`.
6. **Register** the instance with a custom name: `wsl --import CompetitiveProgramming C:\WSL\CompetitiveProgramming C:\WSL\UbuntuBackup.tar`.
7. Open Terminal and **select** your **new Ubuntu instance** `CompetitiveProgramming` from the `+` dropdown.

## Ubuntu Setup (Everyone)
1. **Update** everything: `sudo apt update && sudo apt upgrade -y`.
2. Install **development tools**: `sudo apt install -y build-essential git`.
3. Install your preferred **IDE** or **text editor** (e.g., install **Visual Studio Code** on **Windows**: https://code.visualstudio.com/download, and add the **extensions** `WSL` and `C/C++`).
4. **Clone** this **GitHub repo**: `git clone https://github.com/FreGeh/competitiveProgrammingSetup.git CompetitiveProgramming`.
5. Navigate to the new folder: `~/CompetitiveProgramming`.
6. Open the folder or `program.cpp` in your IDE/text editor (**VSCode**: `code .`).

# Solve a Problem on Codeforces

## 1. Choose a Problem
1. Visit **Codeforces** (https://codeforces.com/) and log in or sign up.
2. For starter problems, go to `Problemsets` and sort by the number of people who have solved them. For example, **Medium Number** (https://codeforces.com/problemset/problem/1760/A).

## 2. Solve the Problem
1. **Read** the problem description carefully.
2. **Paste** the **example input** into `input.txt` and the example output into `output.txt`.
3. **Think of a solution** and write it in the `void run_case()` function.

## 3. Compile and Test Locally
1. **Open** your **Ubuntu Terminal** in `~/CompetitiveProgramming` and compile your code: `g++ -std=c++20 -O2 -Wall program.cpp -o program`.
2. **Test** with example input: `./program < input.txt`.
3. **Compare** output:
   - If **correct**, submit.
   - If **incorrect**, debug with the `debug()` function, place it anywhere you want to analyze the variable behaviour.

## 4. Submit Your Solution
1. Scroll down and select `GNU G++20` under `Submit?`. **Upload your c++ code**, then click `Submit`.
2. Check your **submissions page** for the verdict. If a test fails, copy the test case to debug locally.

# Explanations

## program.cpp

### Head
`#include <bits/stdc++.h>` to include all **standard library headers**. *You can also include each header separately.*
`using namespace std;` to avoid the annoying prefix `std::`.
`typedef long long ll;` to shorten `long long` to `ll`.

```cpp
#ifdef DEBUG
#include "debug.h"
#else
#define debug(...) do { } while(0)
#endif
```
**Conditional compilation**: Include **debug utilities** if defined (`-DDEBUG`) by including our own debug header file. Otherwise, the debug function does nothing.

### Body
`void solve()` is the function where you handle the logic for each test case. Variables are taken from `cin`, and results are outputted via `cout`.

The `main()` function manages setup and execution:
- Optimizes I/O with `ios::sync_with_stdio(false);`.
- Disables automatic flushing of `cout` unless debugging is enabled.
- Reads the number of test cases and executes `solve()` for each.

If the problem has no test cases, set `int tests = 1` and comment out `cin >> tests;`.

## debug.h
- `#pragma once`: Ensures the header file is included **only once** in the program to prevent redefinitions.
- `dbg_out()` (base case): Prints a newline when no arguments are passed, acting as the **termination point** for recursive calls.
- `dbg_out(Head, Tail...)`: A templated function that recursively processes and outputs multiple arguments to `cerr`, separated by spaces.
- `#define debug(...)`: A **macro** that:
  - Prints debug messages to `cerr` in red (`\033[31m`), including the **file name** (`__FILE__`) and **line number** (`__LINE__`) where the macro is called.
  - **Formats** the **output** by displaying the variable names (`#__VA_ARGS__`) followed by their values, leveraging the `dbg_out` function.
  - **Resets text formatting** with `\033[0m`.

This setup allows efficient debugging by integrating **variable inspection** directly into your code **without impacting the production build**.

# Commandline Usage

## Compiling
`g++ -std=c++20 -O2 -Wall -DDEBUG program.cpp -o program`

- **`g++`**: GNU Compiler Collection (GCC) **C++ Compiler**.
- **`-std=c++20`**: Specifies that the **C++20 standard** should be used.
- **`-O2`**: Enables **level 2 optimizations** during compilation, improving runtime performance.
- **`-Wall`**: Activates all **basic warning** messages.
- **`-DDEBUG`**: Includes our **debug utilities** if required.
- **`-o program`**: Specify the name of the **output file**.

## Input and Output
- `./program < input.txt`: Uses `input.txt` as input.
- `./program < input.txt > output.txt`: Saves output to `output.txt`.

# Where to Go Next

Competitive Programming is a **transformative journey** that changes how you approach problems in all aspects of life. It enhances your **logical thinking**, benefits your **career**, and strengthens your **studies**. Start exploring further to continuously improve and grow.

## Online Resources
- **Codeforces** (Top problem-solving platform): [codeforces.com](https://codeforces.com/)
- **CP-Algorithms Wiki** (Helpful articles and guides): [cp-algorithms.com](https://cp-algorithms.com/)
- **GeeksforGeeks CP Handbook** (Step-by-step chapters): [geeksforgeeks.org/competitive-programming-cp-handbook-with-complete-roadmap](https://www.geeksforgeeks.org/competitive-programming-cp-handbook-with-complete-roadmap/)
- **MIT OpenCourseWare** (Free video lectures and resources): 
  - Algorithms: [ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020/)
  - Advanced Algorithms: [ocw.mit.edu/courses/6-854j-advanced-algorithms-fall-2008](https://ocw.mit.edu/courses/6-854j-advanced-algorithms-fall-2008/)
- **Algorithms by Robert Sedgewick and Kevin Wayne** (Highly-rated online book): [algs4.cs.princeton.edu/home](https://algs4.cs.princeton.edu/home/)
- **CP Ressources Wiki**: [github.com/lnishan/awesome-competitive-programming](https://github.com/lnishan/awesome-competitive-programming)