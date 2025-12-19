#ifndef SOLVER_H
#define SOLVER_H

#include "maze.hpp"
#include <vector>
#include <utility>

class Solver {
public:
    Solver(const Maze& m);

    // A* shortest path
    std::vector<std::pair<int,int>> solveAStar();

    // Tremaux algorithm (DFS with marking visited paths)
    std::vector<std::pair<int,int>> solveTremaux();

private:
    const Maze& maze;
    int nr, nc;

    // Helper to check if move is valid (no wall)
    bool canMove(int r1, int c1, int r2, int c2) const;

    // Manhattan heuristic for A*
    int heuristic(int r, int c) const;

    #ifdef UNIT_TEST
	public:

        // Ici on rends la fonction heuristic public pour pouvoir le tester

	int heuristic_public(int r, int c) const {
        return heuristic(r, c);
    }
    #endif
	
};

#endif

