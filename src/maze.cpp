#include <iostream>
#include <vector>

#include "maze.h"


char Maze::select (char c, int d){
    return (rand() % 100 < d) ? c : ' ' ;
}

void Maze::generate(Maze m){
    int r, c;
    //Top of the maze
    for(std::size_t col ; col < nc - 1; col ++){
        
    }
    
    /// Core of the Maze
    //for(std::size_t row = 1; row < nr; row ++){
    //    for(std::size_t col ; col < nc - 1; col ++){
            
    //    }
    //}
    
    ///  Right side of the maze
    //for(std::size_t row = 1; row < nr; row ++){
        
    //}}


