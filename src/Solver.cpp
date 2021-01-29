#include "Solver.hpp"

int OpenNodesEver = 0;

static int GetZeroRow(const Puzzle &puzzle) {
    int size = puzzle.GetSize();

    for (int row = size - 1; row >= 0; --row) {
        for (int column = 0; column < size; ++column) {
            if (puzzle.At(row, column) == 0) {
                return size - row;
            }
        }
    }

    throw std::logic_error("Not found zero element");
}

static int CountInversions(const Puzzle &puzzle) {
    int inversions = 0;

    size_t internalSize = puzzle.GetSize() * puzzle.GetSize();
    for (size_t i = 0; i < internalSize; ++i) {
        for (size_t j = i + 1; j < internalSize; ++j) {
            if (puzzle.At(i) != 0 && puzzle.At(j) != 0 && puzzle.At(i) > puzzle.At(j)) {
                ++inversions;
            }
        }
    }

    return inversions;
}

static void AddChildrenNode(Node *parent,
                     OpenNodes &openNodes,
                     ClosedNodes &closedNodes,
                     const IMove &move,
                     Heuristics::Type heuristicsType) {
    Puzzle *new_puzzle = move.Execute(parent->GetPuzzle());
    
    // Corner zero cell positions
    if (new_puzzle == nullptr) {
        return;
    }
    
    Node *temp = new Node(*new_puzzle, heuristicsType, parent);
    delete new_puzzle;
    
    if (closedNodes.find(temp) != closedNodes.end()) {
        delete temp;
    } else {
        openNodes.push(temp);
        OpenNodesEver++;
    }
}

static void AddChildrenNodes(Node *parent,
                      OpenNodes &openNodes,
                      ClosedNodes &closedNodes,
                      Heuristics::Type heuristicsType) {
    AddChildrenNode(parent, openNodes, closedNodes, MoveLeft(), heuristicsType);
    AddChildrenNode(parent, openNodes, closedNodes, MoveRight(), heuristicsType);
    AddChildrenNode(parent, openNodes, closedNodes, MoveDown(), heuristicsType);
    AddChildrenNode(parent, openNodes, closedNodes, MoveUp(), heuristicsType);
}

std::vector<Node *> GetSolveNodes(Node *finishNode)
{
	std::vector<Node *> nodes;
	
	while (finishNode)
	{
		nodes.push_back(finishNode);
		finishNode = finishNode->GetParent();
	}
	
	return nodes;
}

bool Solver::IsSolvable(const Puzzle &puzzle) {
	int inversions = CountInversions(puzzle);
	if (puzzle.GetSize() % 2 != 0) {
		return inversions % 2 == 0;
	} else {
		int zeroRow = GetZeroRow(puzzle);
		return (inversions + zeroRow) % 2 == 1;
	}
}

void Solver::Solve(const Puzzle &puzzle,
				   Heuristics::Type heuristicsType,
				   OpenSetComparator::Type algorithmType) {
    ClosedNodes closedNodes;
    OpenNodes openNodes = OpenNodes{OpenSetComparator(algorithmType)};
    openNodes.push(new Node(puzzle, heuristicsType));
    OpenNodesEver++;
    
    Node *currentNode;
    while (true) {
        if (openNodes.empty()) {
			throw std::runtime_error("map is incorrect");
        }
	
		currentNode = openNodes.top();
        openNodes.pop();
        closedNodes.insert(currentNode);
        
        if (currentNode->GetPuzzle().IsResolved()) {
//            std::cout << *currentNode;
//            std::cout << "closed nodes: " << closedNodes.size() << std::endl;
//            std::cout << "open nodes: " << openNodes.size() << std::endl;
//            std::cout << std::endl;
//            while (currentNode != nullptr) {
//                std::cout << *currentNode << std::endl;
//				currentNode = currentNode->GetParent();
//            }
			//TODO I know you will burn because of globals and output in this function :)
			std::vector<Node *> solveNodes = GetSolveNodes(currentNode);
			for (int i = solveNodes.size() - 1; i >= 0; i--)
				std::cout << *solveNodes[i] << std::endl;
			std::cout << "Open nodes ever: " << OpenNodesEver << std::endl;
			std::cout << "Maximum number of nodes: " << openNodes.size() + closedNodes.size() << std::endl;
			std::cout << "Moves to solve puzzle: " << solveNodes.size() << std::endl;
            return;
        }
        
        AddChildrenNodes(currentNode, openNodes, closedNodes, heuristicsType);
    }
}
