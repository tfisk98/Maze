#include "solver.hpp"
#include <queue>
#include <map>
#include <set>
#include <cmath>
#include <stack>
#include <algorithm>

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

// ---------------------------
// Manhattan heuristic
// ---------------------------
int Solver::heuristic(int r, int c) const {
    return abs(r - (nr-1)) + abs(c - (nc-1));
}

// ---------------------------
// A* shortest path
// ---------------------------
std::vector<std::pair<int,int>> Solver::solveAStar() {
    using Cell = std::pair<int,int>;
    std::priority_queue<std::pair<int, Cell>,
                        std::vector<std::pair<int, Cell>>,
                        std::greater<>> openSet;

    std::map<Cell, Cell> cameFrom;
    std::map<Cell,int> gScore;
    Cell start{0,0}, goal{nr-1, nc-1};
    gScore[start] = 0;
    openSet.push({heuristic(0,0), start});

    while (!openSet.empty()) {
        auto [f, current] = openSet.top(); openSet.pop();
        if (current == goal) break;

        int r = current.first;
        int c = current.second;
        Cell neighbors[4] = {{r-1,c},{r+1,c},{r,c-1},{r,c+1}};
        for (auto &n : neighbors) {
            int nr2 = n.first;
            int nc2 = n.second;
            if (!canMove(r,c,nr2,nc2)) continue;
            int tentative_g = gScore[current] + 1;
            if (!gScore.count(n) || tentative_g < gScore[n]) {
                gScore[n] = tentative_g;
                int fScore = tentative_g + heuristic(nr2,nc2);
                openSet.push({fScore, n});
                cameFrom[n] = current;
            }
        }
    }

    // Reconstruct path
    std::vector<Cell> path;
    Cell current = goal;
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
    using Cell = std::pair<int,int>;
    std::vector<Cell> path;
    std::stack<Cell> stack;
    std::set<Cell> visited;

    Cell start{0,0}, goal{nr-1, nc-1};
    stack.push(start);
    visited.insert(start);

    while (!stack.empty()) {
        Cell current = stack.top();
        path.push_back(current);

        if (current == goal) break;

        int r = current.first;
        int c = current.second;
        Cell neighbors[4] = {{r-1,c},{r+1,c},{r,c-1},{r,c+1}};
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

