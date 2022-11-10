# N-puzzle solver

## MacOS - ![Build](https://github.com/dolovnyak/n-puzzle/actions/workflows/build.yml/badge.svg?branch=main)

This program solves puzzles of various sizes using various search and heuristic algorithms.
----------
Search algorithms:
----------
- `Greedy search` - finds a solution using only heuristics.
- `Uniform search / Brute-force search` - finds a solution using only depth.
- `A-star search` - finds a solution using depth with heuristic.
###
Heuristics:
----------
- `Manhattan distance / Taxicab geometry` - for each tile, there is distance (number of tiles away) from it’s target position. Manhattan distance returns sum of all these distances.
- `Hamming distance` - the number of tiles that are not in their final position.
- `Linear Conflict + Manhattan Distance / Taxicab geometry` - Two tiles are in a linear conflict if they are in the same row or column, and their target positions are in the same row or column, and the target position of one of the tiles is blocked by the other tile in that row. This heuristic return Manhattan Distance result + linear conflicts (above) * 2.
###

Build and run on `MacOS`:
-------
```
git submodule update --init --recursive
cmake -S . -B build
make -C build
./n_puzzle resources/solvableX_X.txt
```

Options:
---------
```
./n_puzzle --help
Usage: n-puzzle [options] start_puzzle 

Positional arguments:
start_puzzle                    specify the start puzzle file. [required]

Optional arguments:
--help                          shows help message and exits
--version                       prints version information and exits
-t --target_puzzle_filename     specify the target puzzle file.
-h --heuristics                 specify the heuristics function [manhattan, hamming, linear_conflicts]. Default - manhattan [default: 1]
-a --algorithm                  specify the algorithm [greedy, a-star, uniform]. Default - a-star [default: 2]

```

Remarks:
--------
- ### By default, the program has a non-standard solution form, it's like a snake format, but you can change solution (target) format with options.
  ### Default snake solution form:
  ![](https://github.com/dolovnyak/n-puzzle/blob/main/screenshots/Screen%20Shot%202021-05-17%20at%205.46.39%20PM.png)
- ### In output there are values: `h d r` which mean:
  - `h` - heuristic
  - `d` - depth
  - `s` - heuristic and depth sum
- ### There is npuzzle-gen.py which generate random puzzles.

Example:
-------
```
./n_puzzle resources/solvable3_2.txt -h linear_conflicts -a greedy
h: 12, d: 0, s: 12
8 4 1
6 0 2
7 3 5

h: 11, d: 1, s: 12
8 0 1
6 4 2
7 3 5

h: 10, d: 2, s: 12
8 1 0
6 4 2
7 3 5

h: 11, d: 3, s: 14
8 1 2
6 4 0
7 3 5

h: 10, d: 4, s: 14
8 1 2
6 0 4
7 3 5

h: 9, d: 5, s: 14
8 1 2
0 6 4
7 3 5

h: 8, d: 6, s: 14
0 1 2
8 6 4
7 3 5

h: 5, d: 7, s: 12
1 0 2
8 6 4
7 3 5

h: 4, d: 8, s: 12
1 2 0
8 6 4
7 3 5

h: 5, d: 9, s: 14
1 2 4
8 6 0
7 3 5

h: 6, d: 10, s: 16
1 2 4
8 0 6
7 3 5

h: 5, d: 11, s: 16
1 2 4
8 3 6
7 0 5

h: 6, d: 12, s: 18
1 2 4
8 3 6
7 5 0

h: 7, d: 13, s: 20
1 2 4
8 3 0
7 5 6

h: 6, d: 14, s: 20
1 2 0
8 3 4
7 5 6

h: 7, d: 15, s: 22
1 0 2
8 3 4
7 5 6

h: 8, d: 16, s: 24
1 3 2
8 0 4
7 5 6

h: 7, d: 17, s: 24
1 3 2
8 5 4
7 0 6

h: 6, d: 18, s: 24
1 3 2
8 5 4
7 6 0

h: 7, d: 19, s: 26
1 3 2
8 5 0
7 6 4

h: 8, d: 20, s: 28
1 3 2
8 0 5
7 6 4

h: 7, d: 21, s: 28
1 0 2
8 3 5
7 6 4

h: 6, d: 22, s: 28
1 2 0
8 3 5
7 6 4

h: 7, d: 23, s: 30
1 2 5
8 3 0
7 6 4

h: 6, d: 24, s: 30
1 2 5
8 3 4
7 6 0

h: 7, d: 25, s: 32
1 2 5
8 3 4
7 0 6

h: 8, d: 26, s: 34
1 2 5
8 0 4
7 3 6

h: 7, d: 27, s: 34
1 2 5
8 4 0
7 3 6

h: 6, d: 28, s: 34
1 2 0
8 4 5
7 3 6

h: 7, d: 29, s: 36
1 0 2
8 4 5
7 3 6

h: 8, d: 30, s: 38
1 4 2
8 0 5
7 3 6

h: 7, d: 31, s: 38
1 4 2
8 3 5
7 0 6

h: 6, d: 32, s: 38
1 4 2
8 3 5
7 6 0

h: 5, d: 33, s: 38
1 4 2
8 3 0
7 6 5

h: 4, d: 34, s: 38
1 4 2
8 0 3
7 6 5

h: 3, d: 35, s: 38
1 0 2
8 4 3
7 6 5

h: 2, d: 36, s: 38
1 2 0
8 4 3
7 6 5

h: 1, d: 37, s: 38
1 2 3
8 4 0
7 6 5

h: 0, d: 38, s: 38
1 2 3
8 0 4
7 6 5

Time used: 0.2s
Open nodes ever: 161
Maximum number of nodes: 161
Moves to solve puzzle: 39
```
