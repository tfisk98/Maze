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
    int                        walls_nb;
    double                   walls_prct;
    std::vector<Cell>     data;

    
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
    
    Maze(std::size_t nr0 = 0, std::size_t nc0 = 0, int nbw = 0, double wp = 0.): nr(nr0 + 1), nc(nc0 + 1), walls_nb(nbw), walls_prct(wp) {
        std::vector<Cell> datana(nr*nc, empty_cell);
        std::cout<<datana[0].left << std::endl;
        data = datana;
    }
          
          
          /// Top of the maze
          //for(std::size_t col ; col < nc - 1; col ++){
              
          //}
          
          /// Core of the Maze
          //for(std::size_t row = 1; row < nr; row ++){
          //    for(std::size_t col ; col < nc - 1; col ++){
                  
          //    }
          //}
          
          ///  Right side of the maze
          //for(std::size_t row = 1; row < nr; row ++){
              
          //}
    
    Cell
    operator()(const std::size_t& j,
           const std::size_t& k){
        std::cout<<nr << std::endl;
        std::cout<<this->data[0].left << data[0].bot << std::endl;
      return data[j*nc+k];}
      
    const Cell
    operator()(const std::size_t& j,
           const std::size_t& k) const {
      return data[j*nc+k];}
    
    int get_nr(){
        std::cout<<data[0].left <<this->data[0].bot << std::endl;
        return nr;
    }
    
    
    char select(char c, int d);
        //"This function returns a given caracter c here a '|' (side wall) or '+' (floor or roof) with a given percentage d, a space otherwise"
        //return (rand() % 100 < d) ? c : ' ' ;;
    
    void generate(Maze m);
        
        //" This functions generates and displays a given Maze object. Prints a wall on around the maze and inside prints a wall with probability walls_percentage until nb_walls is reached.
       // "
        
        //" sfml pour que l'utilisateur puisse résoudre le maze."
        

    
    
};
    
#endif
