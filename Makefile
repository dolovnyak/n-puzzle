# **************************************************************************** #
# GENERIC_VARIABLES

OBJ_DIR = build

# **************************************************************************** #
# COMPILER_OPTIONS

C_COMPILER = clang
C_STANDART = 
C_CFLAGS =  $(CFLAGS) $(CPPFLAGS) 
C_LFLAGS =  $(CFLAGS) $(CPPFLAGS) 

CPP_COMPILER = clang++
CPP_STANDART = -std=c++1z
CPP_CFLAGS =  $(CXXFLAGS) $(CPPFLAGS) -Wall -Werror -Wextra
CPP_LFLAGS =  $(CXXFLAGS) $(CPPFLAGS) -Wall -Werror -Wextra
# **************************************************************************** #
# N_PUZZLE TARGET DESCRIPTION

N_PUZZLE_NAME = n_puzzle
N_PUZZLE_PATH = src
N_PUZZLE_FILE = ./n_puzzle
N_PUZZLE_SRCS = Heuristics.cpp Move.cpp Node.cpp Parser.cpp Puzzle.cpp Solver.cpp Output.cpp main.cpp
N_PUZZLE_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(N_PUZZLE_SRCS))
N_PUZZLE_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(N_PUZZLE_SRCS))
N_PUZZLE_LIBS = 
N_PUZZLE_INCS = -I include

# **************************************************************************** #
# GENERIC RULES

.PHONY: all re clean fclean
.DEFAULT_GOAL = all

all:  $(N_PUZZLE_FILE)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf  $(N_PUZZLE_FILE)

re: fclean all

$(N_PUZZLE_FILE):  $(N_PUZZLE_OBJS)
	@$(CPP_COMPILER) $(CPP_LFLAGS) $(CPP_STANDART) -o $(N_PUZZLE_FILE) $(N_PUZZLE_OBJS)  $(N_PUZZLE_LIBS)
	@printf 'Finished	\033[1;32m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(N_PUZZLE_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(N_PUZZLE_INCS) -o $@ -c $< -MMD

$(OBJ_DIR)/%.cpp.o: $(N_PUZZLE_PATH)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(CPP_COMPILER) $(CPP_CFLAGS) $(CPP_STANDART) $(N_PUZZLE_INCS) -o $@ -c $< -MMD

-include $(N_PUZZLE_DEPS)
