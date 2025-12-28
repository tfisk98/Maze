/**
 * \file maze.cpp
 * \brief Methodes de la classe Maze (maze.hpp)
 * \author Thomas Burns & Thomas Fisk
 * \version 0.1
 * \date 23/12/2025
 *
 * Corps des methodes introduites dans la classe maze.hpp notamment les fonctions generate, pour lla génération, et print,
 * pour l'affichage terminal.
 *
 *
 */


#include "maze.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <cassert>

// --- Constructor ---
Maze::Maze(std::size_t nr0, std::size_t nc0)
    : nr(nr0), nc(nc0), data(nr0 * nc0, full_cell)
{
}

// --- Operators ---
Cell& Maze::operator()(const std::size_t &j, const std::size_t &k) {
    return data[j * nc + k];
}

const Cell& Maze::operator()(const std::size_t &j, const std::size_t &k) const {
    assert(j < nr && k < nc);
    return data[j * nc + k];
}

// --- Helper ---
bool Maze::in_bounds(int r, int c) const {
    return r >= 0 && r < (int)nr && c >= 0 && c < (int)nc;
}

// --- Generation (Recursive Backtracker) ---
void Maze::generate() {
    // 1. Reset grid
    for (auto &c : data) {
        c.left = '|';
        c.bot  = '_';
        c.visited = false;
    }

    std::mt19937 gen(std::random_device{}());
    
    // DFS Stack
    std::vector<std::pair<int, int>> stack;
    int r = 0, c = 0;
    
    stack.push_back({r, c});
    data[r * nc + c].visited = true;

    // Directions: Up, Down, Left, Right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!stack.empty()) {
        auto [cr, cc] = stack.back();

        // Find unvisited neighbors
        std::vector<int> neighbors;
        for (int i = 0; i < 4; ++i) {
            int nr2 = cr + dr[i];
            int nc2 = cc + dc[i];

            if (in_bounds(nr2, nc2) && !data[nr2 * nc + nc2].visited) {
                neighbors.push_back(i);
            }
        }

        if (neighbors.empty()) {
            stack.pop_back();
        } else {
            // Pick random neighbor
            std::uniform_int_distribution<int> dist(0, neighbors.size() - 1);
            int dir = neighbors[dist(gen)];
            
            int nr2 = cr + dr[dir];
            int nc2 = cc + dc[dir];

            // Remove walls
            // 0: Up, 1: Down, 2: Left, 3: Right
            if (dir == 0)      data[nr2 * nc + nc2].bot = ' '; // Neighbor's bottom
            else if (dir == 1) data[cr * nc + cc].bot = ' ';   // Current's bottom
            else if (dir == 2) data[cr * nc + cc].left = ' ';  // Current's left
            else if (dir == 3) data[nr2 * nc + nc2].left = ' ';// Neighbor's left

            data[nr2 * nc + nc2].visited = true;
            stack.push_back({nr2, nc2});
        }
    }

    std::vector<Wall> candidateWalls;

auto isDeadEnd = [this](int r, int c) {
    int openSides = 0;
    // Check Up
    if (r > 0 && data[(r-1)*nc + c].bot == ' ') openSides++;
    // Check Down
    if (r < (int)nr-1 && data[r*nc + c].bot == ' ') openSides++;
    // Check Left
    if (c > 0 && data[r*nc + c].left == ' ') openSides++;
    // Check Right
    if (c < (int)nc-1 && data[r*nc + c + 1].left == ' ') openSides++;
    return openSides == 1; // only one exit → dead end
};

// Collect removable walls adjacent to dead ends
for (int r = 0; r < (int)nr; ++r) {
    for (int c = 0; c < (int)nc; ++c) {
        if (!isDeadEnd(r,c)) continue;

        // Left wall
        if (c > 0 && data[r*nc + c].left == '|')
            candidateWalls.push_back({r, c, 'L'});
        // Bottom wall
        if (r < (int)nr-1 && data[r*nc + c].bot == '_')
            candidateWalls.push_back({r, c, 'B'});
    }
}

// Shuffle candidates
std::shuffle(candidateWalls.begin(), candidateWalls.end(), gen);

// Remove up to 20% of candidate walls
int removeCount = candidateWalls.size() * 0.20f;
for (int i = 0; i < removeCount; ++i) {
    auto &w = candidateWalls[i];
    if (w.type == 'L') data[w.r*nc + w.c].left = ' ';
    else data[w.r*nc + w.c].bot = ' ';
}


    // Open Entrance (Top-Left) and Exit (Bottom-Right)
    data[0].left = ' '; 
    data[(nr * nc) - 1].bot = ' ';
}

// --- Printing ---
void Maze::print() {
    // Top Roof
    for (std::size_t c = 0; c < nc; ++c) {
        std::cout << " _";
    }
    std::cout << "\n";

    for (std::size_t r = 0; r < nr; ++r) {
        // Left-most wall of the row
        // If data[r*nc].left is empty, it's the entrance
        std::cout << (data[r * nc].left == '|' ? "|" : " ");
        
        for (std::size_t c = 0; c < nc; ++c) {
             // Bottom wall
             std::cout << (data[r * nc + c].bot == '_' ? "_" : " ");
             
             // Right wall? 
             // The right wall of cell C is the left wall of cell C+1.
             if (c < nc - 1) {
                 std::cout << (data[r * nc + c + 1].left == '|' ? "|" : " ");
             } else {
                 // Far right boundary
                 std::cout << "|";
             }
        }
        std::cout << "\n";
    }
}
