/*!
 * \file solver.cpp
 * \brief Methodes de la classe Solver (solver.hpp)
 * \author Thomas Burns & Thomas Fisk
 * \version 0.1
 * \date 23/12/2025
 *
 * Corps des methodes introduites dans la classe solver.hpp, comme les algorithmes Astar, Trémaux.
 *
 */


#include "solver.hpp"
#include <queue>
#include <map>
#include <set>
#include <cmath>
#include <stack>
#include <algorithm>
//#include <catch2/catch_test_macros.hpp>


Solver::Solver(const Maze& m) : maze(m), nr(m.rows()), nc(m.cols()) {}


// ---------------------------
// Check if movement is possible (no wall between (r1,c1) and (r2,c2))
// ---------------------------
bool Solver::canMove(int r1, int c1, int r2, int c2) const {
    if (r2 < 0 || r2 >= nr || c2 < 0 || c2 >= nc) return false;
    if (r2 == r1) { // horizontal move
        if (c2 > c1) return maze(r1,c2).left != '|';   // right
        else         return maze(r1,c1).left != '|';   // left
    } else if (c2 == c1) { // vertical move
        if (r2 > r1) return maze(r1,c1).bot != '_';   // down
        else         return maze(r2,c1).bot != '_';   // up
    }
    return false; // diagonal not allowed
}

/*
bool Solver::canMove(Maze& m,int r1, int c1, int r2, int c2) const {
    if !m.inBounds(r2,c2) return false;
    if (r2 == r1) { // horizontal move
        if (c2 > c1) return maze(r1,c2).left != '|';   // right
        else         return maze(r1,c1).left != '|';   // left
    } else if (c2 == c1) { // vertical move
        if (r2 > r1) return maze(r1,c1).bot != '_';   // down
        else         return maze(r2,c1).bot != '_';   // up
    }
    return false; // diagonal not allowed
}*/

// ---------------------------
// Manhattan heuristic
// ---------------------------
int Solver::manhattan(int r, int c) const {
    return abs(r - (nr-1)) + abs(c - (nc-1));
}

// ---------------------------
// A* shortest path
// ---------------------------
std::vector<std::pair<int,int>> Solver::solveAStar() {
    using CellCoord = std::pair<int,int>;
    std::priority_queue<std::pair<int, CellCoord>,
                        std::vector<std::pair<int, CellCoord>>,
                        std::greater<>> openSet;

    std::map<CellCoord, CellCoord> cameFrom;
    std::map<CellCoord, int> lengthPath;
    CellCoord start{0,0}, goal{nr-1, nc-1};
    lengthPath[start] = 0;
    openSet.push({manhattan(0,0), start});
    
    int r,c,nr1,nc1;
    int potLength;
    int pathScore;

    while (!openSet.empty()) {
        auto [f, current] = openSet.top(); openSet.pop();
        if (current == goal) break;

        r = current.first;
        c = current.second;
        CellCoord neighbors[4] = {{r-1,c},{r+1,c},{r,c-1},{r,c+1}};
        for (auto &nxt_cell : neighbors) {
            nr1 = nxt_cell.first;
            nc1 = nxt_cell.second;
            if (!canMove(r,c,nr1,nc1)) continue;
            potLength = lengthPath[current] + 1;
            if (!lengthPath.count(nxt_cell) || potLength < lengthPath[nxt_cell]) {
                lengthPath[nxt_cell] = potLength;
                pathScore = potLength + manhattan(nr1,nc1);
                openSet.push({pathScore, nxt_cell});
                cameFrom[nxt_cell] = current;
            }
        }
    }

    // Reconstruct path
    std::vector<CellCoord> path;
    CellCoord current = goal;
    path.push_back(current);
    while (current != start) {
        current = cameFrom[current];
        path.push_back(current);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// ---------------------------
// Trémaux's algorithm
// ---------------------------

std::vector<std::pair<int,int>> Solver::solveTremaux() {
    using CellCoord = std::pair<int,int>;
    std::vector<CellCoord> path;
    std::stack<CellCoord> stack;
    std::set<CellCoord> visited;

    CellCoord start{0,0}, goal{nr-1, nc-1};
    stack.push(start);
    visited.insert(start);

    while (!stack.empty()) {
        CellCoord current = stack.top();
        path.push_back(current);

        if (current == goal) break;

        int r = current.first;
        int c = current.second;
        CellCoord neighbors[4] = {{r-1,c},{r+1,c},{r,c-1},{r,c+1}};
        bool moved = false;

        for (auto &n : neighbors) {
            if (visited.count(n)) continue;
            if (!canMove(r,c,n.first,n.second)) continue;
            stack.push(n);
            visited.insert(n);
            moved = true;
            break;
        }

        if (!moved) {
            stack.pop();
            path.pop_back(); // backtrack
        }
    }

    return path;
}

