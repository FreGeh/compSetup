# Introduction

Welcome to the **Competitive Programming Setup Guide**, utilizing a **proven** and **efficient setup** for long-term success!
Whether you're aiming to excel in **contests** like **ICPC** or enhance your coding abilities for **technical interviews**, this guide gets you started quickly and effectively.

By **following** this **guide**, you'll:
- Set up a **contest-like** development environment.
- Master a **pro-like** yet **simple setup** for coding challenges.
- Learn how to **solve problems** on platforms like **Codeforces** from start to finish.

# Table of Contents
- [Environment Setup](#environment-setup)
  - [WSL Setup (Windows Users)](#wsl-setup-windows-users)
  - [Ubuntu Setup (Everyone)](#ubuntu-setup-everyone)
- [Solve a Problem on Codeforces](#solve-a-problem-on-codeforces)
- [Commandline Usage](#commandline-usage)
- [Explanations](#explanations)
- [Where to Go Next](#where-to-go-next)
- [Contribute](#contribute)

# Guide
[Here](./README.md) I write down everything I learn on competitive programming in C++
# Environment Setup

## WSL Setup (Windows Users)
This is for **Windows** Users; **Linux users can skip this**.

Since platforms like **Codeforces** and local contests like ICPC run on **Linux-based OS**, we use **WSL** with **Ubuntu** to match that **official environment** (https://docs.icpc.global/worldfinals-programming-environment/). It's simpler than using Windows tools and doesn't affect speed.

1. Right-click the **Start Menu** -> PowerShell/Terminal (**Admin**).
2. Type `wsl --install`.
3. **Restart** your PC.
4. **Launch Ubuntu** from the Start Menu and set up your user.

### Optional: Rename WSL Instance
<details>
<summary>Click to expand</summary>

If you already have WSL installed or plan to have multiple instances, organizing them helps.

1. **Open** a new PowerShell/Terminal (Admin).
2. Install an **additional instance**: `wsl --install -d Ubuntu-24.04`.
3. Create a **folder** for new WSL instances: `mkdir C:\WSL`.
4. **Export** the instance: `wsl --export Ubuntu-24.04 C:\WSL\UbuntuBackup.tar`.
5. **Unregister** the instance: `wsl --unregister Ubuntu-24.04`.
6. **Register** the instance with a custom name: `wsl --import CompetitiveProgramming C:\WSL\CompetitiveProgramming C:\WSL\UbuntuBackup.tar`.
7. Open Terminal and **select** your **new Ubuntu instance** `CompetitiveProgramming` from the `+` dropdown.
</details>


## Ubuntu Setup (Everyone)
1. **Update** everything: `sudo apt update && sudo apt upgrade -y`.
2. Install **development tools**: `sudo apt install -y build-essential git`.
3. Install your preferred **IDE** or **text editor** (e.g., install **Visual Studio Code** on **Windows**: https://code.visualstudio.com/download, and add the **extensions** `WSL` and `C/C++`).
4. **Clone** this **GitHub repo**: `git clone https://github.com/FreGeh/competitiveProgrammingSetup.git CompetitiveProgramming`.
5. Navigate to the new folder: `cd CompetitiveProgramming/`.
6. Open the folder or `program.cpp` in your IDE/text editor (**VSCode**: `code .`).

# Solve a Problem on Codeforces

## 1. Choose a Problem
1. Visit **Codeforces** (https://codeforces.com/) and log in or sign up.
2. For starter problems, go to `Problemsets` and sort by the number of people who have solved them. For example, **Medium Number** (https://codeforces.com/problemset/problem/1760/A).

## 2. Solve the Problem
1. **Read** the problem description carefully.
2. **Paste** the **example input** into `input.txt` and the example output into `output.txt`.
3. **Think of a solution** and write it in the `void solve()` function.

## 3. Compile and Test Locally
1. **Open** your **Ubuntu Terminal** `cd ~/CompetitiveProgramming` and compile your code: `g++ -std=c++20 -O2 -Wall program.cpp -o program`.
2. **Test** with example input: `./program < input.txt`.
3. **Compare** output:
   - If **correct**, submit.
   - If **incorrect**, debug with the `debug()` function, place it anywhere you want to analyze the variable behaviour.

## 4. Submit Your Solution
1. Scroll down and select `GNU G++20` under `Submit?`. **Upload your c++ code**, then click `Submit`.
2. Check your **submissions page** for the verdict. If a test fails, copy the test case to debug locally further.


# Commandline Usage

## Compiling
```sh
g++ -std=c++20 -O2 -Wall -DDEBUG program.cpp -o program
```

- **`g++`**: GNU Compiler Collection (GCC) **C++ Compiler**.
- **`-std=c++20`**: Specifies that the **C++20 standard** should be used.
- **`-O2`**: Enables **level 2 optimizations** during compilation, improving runtime performance.
- **`-Wall`**: Activates all **basic warning** messages.
- **`-DDEBUG`**: Includes our **debug utilities** if required.
- **`-o program`**: Specify the name of the **output file**.

## Input and Output
- **`./program < input.txt`**: Uses `input.txt` as input.
- **`./program < input.txt > output.txt`**: Saves output to `output.txt`.

# Explanations

## program.cpp

### Head
- **`#include <bits/stdc++.h>`**: Includes all standard library headers in one line. *(Use individual headers to slightly reduce compilation time.)*
- **`using namespace std;`**: Avoids the repetitive prefix `std::`.
- **`typedef long long ll;`**: Shortens `long long` to `ll`.
- **`#ifdef DEBUG`** **Conditional compilation**: If compiled with (**`-DDEBUG`**) includes custom **debug utilities** `#include "debug.h"`. Otherwise `#define debug(...) do { } while(0)` to not interfere if accidentally still used in code.

### Body
**`void solve()`** The main logic for each test case goes here. Inputs are read via `cin` and results are output via `cout`. 

**`main()`** **Function**: Handles setup and test case execution:
- Optimizes I/O: `ios::sync_with_stdio(false);` speeds up input/output operations. 
- Automatic flushing enabled `cin.tie(nullptr);` when not debugging: `#ifndef DEBUG`.
- Reads the number of test cases `tests` and calls `solve()` for each. *(Tip: If the problem has no test cases, set `int tests = 1` and comment out `cin >> tests;`)*

## debug.h
- **`#pragma once`**: Ensures the header file is included **only once** in the program to prevent redefinitions.
- **`dbg_out()`** (base case): Prints a newline when no arguments are passed, acting as the **termination point** for recursive calls.
- **`dbg_out(Head, Tail...)`**: A templated function that recursively processes and outputs multiple arguments to `cerr`, separated by spaces.
- **`#define debug(...)`**: A **macro** that:
  - Prints debug messages to `cerr` in red (`\033[31m`), including the **file name** (`__FILE__`) and **line number** (`__LINE__`) where the macro is called.
  - **Formats** the **output** by displaying the variable names (`#__VA_ARGS__`) followed by their values, leveraging the `dbg_out` function.
  - **Resets text formatting** with `\033[0m`.

This setup allows efficient debugging by integrating **variable inspection** directly into your code **without impacting the production build**.


# Where to Go Next

Competitive Programming is a **transformative journey** that seems way too big and complicated at the beginning, but let's you gradually improve and understand more about many aspects of modern Computer Science. So don't give up easily, but keep going by solving a problem each day :)

## Online Resources
- **Codeforces** (Top problem-solving platform): [codeforces.com](https://codeforces.com/)
- **CP-Algorithms Wiki** (Helpful articles and guides): [cp-algorithms.com](https://cp-algorithms.com/)
- **GeeksforGeeks CP Handbook** (Step-by-step chapters): [geeksforgeeks.org/competitive-programming-cp-handbook-with-complete-roadmap](https://www.geeksforgeeks.org/competitive-programming-cp-handbook-with-complete-roadmap/)
- **MIT OpenCourseWare** (Free video lectures and resources): 
  - Algorithms: [ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020/)
  - Advanced Algorithms: [ocw.mit.edu/courses/6-854j-advanced-algorithms-fall-2008](https://ocw.mit.edu/courses/6-854j-advanced-algorithms-fall-2008/)
- **Algorithms by Robert Sedgewick and Kevin Wayne** (Highly-rated online book): [algs4.cs.princeton.edu/home](https://algs4.cs.princeton.edu/home/)
- **CP Ressources Wiki**: [github.com/lnishan/awesome-competitive-programming](https://github.com/lnishan/awesome-competitive-programming)

## Tools
- **Tampermonkey Script** (Highlights relevant math variables/notations so you can read problems easier): [greasyfork.org](https://greasyfork.org/en/scripts/521888-math-variables-and-notations-highlighter)(*made by me*)

# Contribute

Thank you for the interest in this page :)
I would appreciate any help to keep it up to date and fix any errors and add improvements if needed.

## How
1. For new additions or specific modifications create [Pull Requests](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request)
2. For general suggestions create an [Issue](https://github.com/FreGeh/competitiveProgrammingSetup/issues/new/choose)

## ToDos
- add more ressources, but keep it short
- better explanations that are precise and understandable even for beginners
- add screenshots/gifs where needed
- improve visual appeal
- youtube video going through everything
    - showing how to solve any problem with it