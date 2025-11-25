#include "maze.cpp"
#include <iostream>

int main(){
    
    std::size_t nbrow = 4;
    std::size_t nbcol = 4;
    int wall_nb = 8;
    int walls_prct = 50;
    
    Maze M = Maze(nbrow, nbcol, wall_nb, walls_prct);
    
    Cell first {.left = 'a', .bot='b'};
    char p  = select('j', 100);

    Cell last = M(0,0);
    //first.bot = '+';
    last.left = '|';
    
    std::cout<< "first left:" << first.left << "first bot:" << first.bot << std::endl;
    std::cout<< "last left:" << last.left << "last bot:" << last.bot << std::endl;
    
    M.generate();
    M.print();
    
    return 0;
}
