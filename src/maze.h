#ifndef MAZE_H
#define MAZE_H

#include "cell.h"

#include <iostream>
#include <vector>
#include <memory>



class Maze {
    
    typedef std::tuple<std::size_t,
               std::size_t,
               Cell>  CellContainer;

    typedef std::vector<CellContainer> DataType;
    
    const std::size_t             nr,nc;
    int                         wall_nb;
    double                    walls_prct;
    std::vector<Cell>              data;

    
    ///**
    /// *       \class Maze
    /// *
    /// *       \brief class of maze object
    /// *
    /// *        This class generates a maze grid
    /// *
    /// *
    /// *
    /// */
    
public:
    
    Maze(std::size_t nr0 = 0, std::size_t nc0 = 0, int nbw = 0, double wp = 0.): nr(nr0 + 1), nc(nc0 + 1), wall_nb(nbw), walls_prct(wp) {
        std::vector<Cell> datana(nr*nc, empty_cell);
        data = datana;
    }
        
    
    Cell
    operator()(const std::size_t& j,
           const std::size_t& k){
      return data[j*nc+k];}
      
    const Cell
    operator()(const std::size_t& j,
           const std::size_t& k) const {
      return data[j*nc+k];}

    
    void generate();
        
        //" This functions generates and displays a given Maze object. Prints a wall on around the maze and inside prints a wall with probability walls_percentage until nb_walls is reached.
       // "
        
        //" sfml pour que l'utilisateur puisse résoudre le maze."
        
    void print();

    
    
};
    
#endif
