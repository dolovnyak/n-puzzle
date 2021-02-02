from package import generate_makefile

N_PUZZLE = {
    "type": "prog",
    "out": ".",
    "name": "n_puzzle",
    "path": "src",
    "sources": [
        "Heuristics.cpp",
        "Move.cpp",
        "Node.cpp",
        "Parser.cpp",
        "Puzzle.cpp",
        "Solver.cpp",
        "Output.cpp",
        "main.cpp"
    ],
    "compiler": "cpp",
    "includes": ["include"]
}

COMPILERS = {
    "cpp": {
        "flags": "-Wall -Werror -Wextra",
        "binary": "clang++",
        "std": "-std=c++1z"
    }
}

generate_makefile(N_PUZZLE, COMPILERS)