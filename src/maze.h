#ifndef maze.h
#define maze.h

#inlcude "maze.cpp"
#include "cell.h"

#include <iostream>
#include <vector>

typedef std::vector<std::vector<Cell>> CellContainer;

class Maze {
    <#instance variables#>
    
public:
    std::size_t size;
    int nb_walls;
    double walls_percentage;
    CellContainer data;
    
    Maze(std::size_t sz=1, int nbw=0, double wp= 0.): size(sz), nb_walls(nbw), walls_percentage(wp){};
    
    char select(char c, int d){
        return (rand() % 100 < d) ? c : ' ' ;
    }
    
};
    
#endif
