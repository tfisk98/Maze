#include "maze_TB.hpp"
#include <iostream>

int main() {

    std::size_t nbrow;
    std::size_t nbcol;

    std::cout << "Entrez nombre de lignes :\n";
    std::cin >> nbrow;

    std::cout << "Et nombre de colonnes :\n";
    std::cin >> nbcol;

    Maze M(nbrow, nbcol);

    Cell first { .left = 'a', .bot = 'b' };

    // Reference to modify the maze
    Cell& last = M(0,0);
    last.left = '|';

    std::cout << "first left:" << first.left
              << " first bot:" << first.bot << std::endl;

    std::cout << "last left:" << last.left
              << " last bot:" << last.bot << std::endl;

    M.generate();
    M.print();

    return 0;
}

