#ifndef CELL_H
#define CELL_H

#include <iostream>


struct Cell{char left; char bot ; bool visited; } empty_cell ={' ',' ', false}, full_cell={'|','_',false};

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
     *
     */




#endif
