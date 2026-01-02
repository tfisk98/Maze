#include "maze.hpp"
#include <iostream>

int main() {
    std::size_t nbrow;
    std::size_t nbcol;

    std::cout << "Entrez le nombre de lignes :";
    std::cin >> nbrow;
    std::cout << "Entrez le nombre de colonnes :";
    std::cin >> nbcol;

    Maze M(nbrow, nbcol);

    M.generate();
    M.print();

    return 0;
}

