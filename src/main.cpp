#include "maze.cpp"
#include <iostream>

int main(){
    
    std::size_t nbrow = 3;
    std::size_t nbcol = 3;
    int nb_walls = 10;
    double walls_prob = 0.15;
    
    std::cout<<nb_walls<< std::endl;
    Maze M = Maze(nbrow, nbcol, nb_walls, walls_prob);
    
    Cell first {.left = 'a', .bot='b'};
    char p  = M.select('j', 100);
    std::cout << M.get_nr() << std::endl;
    Cell last = M(0,0);
    //first.bot = '+';
    //last.left = '|';
    
    std::cout<< "first left:" << first.left << "first bot:" << first.bot << std::endl;
    std::cout<< "last left:" << last.left << "last bot:" << last.bot << std::endl;
    
    return 0;
}
