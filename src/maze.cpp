#include <iostream>
#include <vector>

#include "maze.h"


char select (char c, int d){
    return (rand() % 100 < d) ? c : ' ' ;
}

void Maze::generate(){
    int wall_count = 0;
    //Top of the maze
    for(std::size_t col=1 ; col < nc - 1; col ++){
        data[col].bot = '_';
    }
    
    /// Core of the Maze
    for(std::size_t row = 1; row < nr; row ++){
        data[row*nc].left = '|';
        for(std::size_t col = 1 ; col < nc - 1; col ++){
            if(wall_count < wall_nb){
                data[row*nc + col].left = select('|',walls_prct);
                data[row*nc + col].bot = select('_',walls_prct);
                if(data[row*nc + col].left == '|'){
                    wall_count ++;
                }
                if(data[row*nc + col].bot == '_'){
                    wall_count ++;
                }
                
            }
        }
        data[row*nc + nc-1].left = '|';
    }
    
    ///Bottom of the maze
    for(std::size_t col=0 ; col < nc-2; col ++){
        data[nr*(nc -1) + col].bot = '_';
    }
    
    
}

void Maze::print(){
    for(std::size_t row = 0; row < nr; row ++){
        for(std::size_t col =0; col < nc; col ++){
            std::cout<<data[row*nc + col].left << data[row*nc + col].bot;
        }
        std::cout<<std::endl;
    }
}


