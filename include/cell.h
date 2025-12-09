#ifndef CELL_H
#define CELL_H

#include <iostream>

struct Cell {
    char left; 
    char bot; 
    bool visited;
};

static Cell empty_cell = {' ', ' ', false};
static Cell full_cell  = {'|', '_', false};

#endif

