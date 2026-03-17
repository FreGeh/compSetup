# ════════════════════════════════════════════════════════════
#  Competitive Programming Makefile
#  Structure:  ./main.cpp   ./tests/1.in  ./tests/1.ans  …
#
#  make          – compile
#  make run      – run interactively (stdin)
#  make test     – run all tests/ cases with timing + visual diff
#  make t N=3    – run single test case #3
#  make add      – append a new empty test case
#  make new DIR=A – scaffold a new task directory
#  make clean    – remove binary
# ════════════════════════════════════════════════════════════

TASK      = main
CXX       = g++
CXXFLAGS  = -std=c++20 -Wall -Wextra -Wshadow -O2 \
            -D_GLIBCXX_DEBUG -DDEBUG \
            -fsanitize=address,undefined

TESTS_DIR = tests
SHELL     := /bin/bash

# ── ANSI colours ─────────────────────────────────────────────
R  := \033[0;31m
G  := \033[0;32m
Y  := \033[1;33m
C  := \033[0;36m
B  := \033[1m
D  := \033[2m
RS := \033[0m

# ── Inline Python visual-diff script ─────────────────────────
define DIFF_PY
import sys
from difflib import SequenceMatcher

G  = '\033[0;32m'
R  = '\033[0;31m'
RB = '\033[41;1m'
D  = '\033[2m'
RS = '\033[0m'

exp_lines = open(sys.argv[1]).read().rstrip('\n').splitlines()
got_lines = open(sys.argv[2]).read().rstrip('\n').splitlines()

n = max(len(exp_lines), len(got_lines))
fails = 0
for i in range(n):
    if i >= len(got_lines):
        print(f"{R}  ✗  {exp_lines[i]}{RS}  {D}← missing line{RS}")
        fails += 1
    elif i >= len(exp_lines):
        print(f"{R}  +  {got_lines[i]}{RS}  {D}← extra line{RS}")
        fails += 1
    elif got_lines[i].split() == exp_lines[i].split():
        print(f"{G}  ✓  {got_lines[i]}{RS}")
    else:
        fails += 1
        sm = SequenceMatcher(None, exp_lines[i], got_lines[i])
        out = R + '  ✗  '
        for op, a0, a1, b0, b1 in sm.get_opcodes():
            chunk = got_lines[i][b0:b1]
            if op == 'equal':
                out += chunk
            else:
                out += RB + chunk + RS + R
        print(out + RS)
        print(f"{D}     exp: {exp_lines[i]}{RS}")
sys.exit(fails)
endef
export DIFF_PY

# ── Inline C++ Debug Template ────────────────────────────────
define DEBUG_H
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
  #define debug(...) do { cerr << "\033[31m" << "[" << __FILE__ << ":" << __LINE__ << "] (" << #__VA_ARGS__ << "):" << "\033[0m"; dbg::out(cerr, __VA_ARGS__); } while (0)
#else
  #define debug(...) do { } while (0)
#endif
endef
export DEBUG_H

.PHONY: all run test t add clean new
.ONESHELL:

# ── Build ─────────────────────────────────────────────────────
all: $(TASK)

$(TASK): $(TASK).cpp
	@printf "$(C)$(B)Compiling $(TASK).cpp …$(RS)\n"
	$(CXX) $(CXXFLAGS) $< -o $@ \
		&& printf "$(G)$(B)✓  Build OK$(RS)\n"

# ── Interactive run ───────────────────────────────────────────
run: $(TASK)
	@./$(TASK)

# ── Single test:  make t N=2 ──────────────────────────────────
t: $(TASK)
	@echo "$$DIFF_PY" > /tmp/_cp_diff.py
	n="$(N)"
	inf="$(TESTS_DIR)/$$n.in"
	ans="$(TESTS_DIR)/$$n.ans"
	[ -n "$$n" ] || { printf "$(R)Usage: make t N=<num>$(RS)\n"; exit 1; }
	[ -f "$$inf" ] || { printf "$(R)No such file: $$inf$(RS)\n"; exit 1; }
	printf "$(C)$(B)── Test $$n ──────────────────────────────$(RS)\n"
	printf "$(D)input:$(RS)\n"; sed 's/^/  /' "$$inf"; printf "\n"
	start=$$(date +%s%N)
	actual=$$(./$(TASK) < "$$inf" 2>&1); rc=$$?
	end=$$(date +%s%N)
	ms=$$(( (end - start) / 1000000 ))
	if [ $$rc -ne 0 ]; then
		printf "$(R)$(B)💥 RUNTIME ERROR$(RS)$(D)  exit=$$rc  $${ms}ms$(RS)\n"
		echo "$$actual" | sed 's/^/  /'
	elif [ -f "$$ans" ]; then
		echo "$$actual" > /tmp/_cp_actual.txt
		if python3 /tmp/_cp_diff.py "$$ans" /tmp/_cp_actual.txt; then
			printf "$(G)$(B)✅ PASSED$(RS)$(D)  $${ms}ms$(RS)\n"
		else
			printf "$(R)$(B)❌ FAILED$(RS)$(D)  $${ms}ms$(RS)\n"
		fi
	else
		printf "$(Y)⚠  no .ans$(RS)$(D)  $${ms}ms$(RS)\n"
		echo "$$actual" | sed 's/^/  /'
	fi

# ── All tests ─────────────────────────────────────────────────
test: $(TASK)
	@echo "$$DIFF_PY" > /tmp/_cp_diff.py
	pass=0; fail=0
	for inf in $$(ls -v $(TESTS_DIR)/*.in 2>/dev/null); do
		n=$$(basename "$$inf" .in)
		ans="$(TESTS_DIR)/$$n.ans"
		start=$$(date +%s%N)
		actual=$$(./$(TASK) < "$$inf" 2>&1); rc=$$?
		end=$$(date +%s%N)
		ms=$$(( (end - start) / 1000000 ))
		printf "$(C)$(B)── Test $$n$(RS)$(D)  $${ms}ms$(RS)\n"
		if [ $$rc -ne 0 ]; then
			printf "$(R)$(B)💥 RUNTIME ERROR$(RS)$(D)  exit=$$rc$(RS)\n"
			echo "$$actual" | sed 's/^/   /'
			fail=$$((fail+1))
		elif [ -f "$$ans" ]; then
			echo "$$actual" > /tmp/_cp_actual.txt
			if python3 /tmp/_cp_diff.py "$$ans" /tmp/_cp_actual.txt; then
				printf "$(G)$(B)✅ PASSED$(RS)\n"
				pass=$$((pass+1))
			else
				printf "$(R)$(B)❌ FAILED$(RS)\n"
				fail=$$((fail+1))
			fi
		else
			printf "$(Y)⚠  no .ans$(RS)\n"
			echo "$$actual" | sed 's/^/   /'
		fi
	done
	total=$$((pass+fail))
	printf "$(D)────────────────────────────────────$(RS)\n"
	if [ $$total -eq 0 ]; then
		printf "$(Y)No .in files found in $(TESTS_DIR)/$(RS)\n"
	elif [ $$fail -eq 0 ]; then
		printf "$(G)$(B)🎉  ALL $$total / $$total PASSED$(RS)\n"
	else
		printf "  $(G)$$pass ✅  $(R)$$fail ❌  $(D)/ $$total$(RS)\n"
	fi

# ── Add next empty test case ──────────────────────────────────
add:
	@n=$$(ls $(TESTS_DIR)/*.in 2>/dev/null | wc -l); n=$$((n+1))
	touch "$(TESTS_DIR)/$$n.in" "$(TESTS_DIR)/$$n.ans"
	printf "$(G)Created test $$n  →  $(TESTS_DIR)/$$n.in  $(TESTS_DIR)/$$n.ans$(RS)\n"

# ── Scaffold a new task directory:  make new DIR=A ────────────
new:
	@[ -n "$(DIR)" ] || { printf "$(R)Usage: make new DIR=<n>$(RS)\n"; exit 1; }
	mkdir -p "$(DIR)/$(TESTS_DIR)" "$(DIR)/templates"
	[ -f "$(DIR)/$(TASK).cpp" ] || touch "$(DIR)/$(TASK).cpp"
	touch "$(DIR)/$(TESTS_DIR)/1.in" "$(DIR)/$(TESTS_DIR)/1.ans"
	echo "$$DEBUG_H" > "$(DIR)/templates/debug.h"
	cp Makefile "$(DIR)/Makefile"
	printf "$(G)$(B)✓  Created $(DIR)/$(RS)\n"
	printf "$(D)  $(DIR)/$(TASK).cpp\n  $(DIR)/$(TESTS_DIR)/1.in\n  $(DIR)/$(TESTS_DIR)/1.ans\n  $(DIR)/templates/debug.h$(RS)\n"

# ── Remove build artifacts ────────────────────────────────────
clean:
	@rm -f $(TASK) *.o
	printf "$(Y)Cleaned$(RS)\n"