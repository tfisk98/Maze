#ifndef MAZE_H
#define MAZE_H

#include "cell.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <random>


class Maze {
public:
    Maze(std::size_t nr0 = 0, std::size_t nc0 = 0);

    Cell& operator()(const std::size_t &j, const std::size_t &k);
    const Cell& operator()(const std::size_t &j, const std::size_t &k) const;

    std::size_t rows() const {return nr; }
    std::size_t cols() const {return nc; }

    void generate();
    void print();

private:
    bool in_bounds(int r, int c) const;

    std::size_t nr, nc;
    std::vector<Cell> data;
};


#endif

