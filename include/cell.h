#ifndef CELL_H
#define CELL_H

#include <iostream>

<<<<<<< HEAD
struct Cell {
    char left; 
    char bot; 
    bool visited;
};

static Cell empty_cell = {' ', ' ', false};
static Cell full_cell  = {'|', '_', false};

#endif

=======

struct Cell{char left; char bot ; bool visited; double size;} empty_cell ={' ',' ', false, 10.}, full_cell={'|','_',false,10.};

//struct Path{std::tuple<std::size_t, std::size_t> act, std::tuple<std::size_t, std::size_t> next };


    /**
     *       \struct Cell
     *
     *       \brief Object of Maze
     *
     *        This is a single cell unit
     *
     *          left is ' |' for a wall, ' ' else
     *          bot is '++' for a wall, ' ' otherwise
     *              visited is True if cell is visited, False otherwise
     *              size is a positive double corresponding to the number of pixels on a side
     *
     */




#endif
>>>>>>> 811fd5c (Reorg)
