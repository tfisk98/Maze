#ifndef SOLVER_H
#define SOLVER_H

/**
 * \file solver.hpp
 * \brief Classe Solver
 * \author Thomas Burns & Thomas Fisk
 * \version 0.1
 * \date 23/12/2025
 *
 * Contient la classe solver qui gère la résolution du labyrinthe.
 * 
 */

#include "maze.hpp"
#include <vector>
#include <utility>


/**
* \class Solver
* \brief classe representant le solver, le résoluteur
*
*  La classe gere la résolution du labrinthe a travers l'algorithme AStar et/ou l'algorithme Trémaux.
*
*/

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

