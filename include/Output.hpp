#pragma once

#include <vector>

#include "Node.hpp"
#include "Solver.hpp"

#define RESET   "\033[0m"

#define FOREGROUND_BLACK   "\033[30m"
#define FOREGROUND_RED     "\033[31m"
#define FOREGROUND_GREEN   "\033[32m"
#define FOREGROUND_YELLOW  "\033[33m"
#define FOREGROUND_BLUE    "\033[34m"
#define FOREGROUND_MAGENTA "\033[35m"
#define FOREGROUND_CYAN    "\033[36m"
#define FOREGROUND_WHITE   "\033[37m"

#define BACKGROUND_BLACK   "\033[40m"
#define BACKGROUND_RED     "\033[41m"
#define BACKGROUND_GREEN   "\033[32m"
#define BACKGROUND_YELLOW  "\033[33m"
#define BACKGROUND_BLUE    "\033[34m"
#define BACKGROUND_MAGENTA "\033[35m"
#define BACKGROUND_CYAN    "\033[36m"
#define BACKGROUND_WHITE   "\033[37m"

#include <iostream>

#include "Exceptions.hpp"

class Output {
public:
    static void PrintSolveSteps(const Solver::SolverResult &solver_result);
};
