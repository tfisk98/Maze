/**
 * \file main.cpp
 * \brief Fichier principal
 * \author Thomas Burns & Thomas Fisk
 * \version 0.1
 * \date 23/12/2025
 *
 * Fichier principal. Programme à exécuter.
 * Demande à l'utilisateur un nombre de ligne et un nombre de colonnes.
 * Lance la génération du labyrinthe.
 * Affiche le Labyrinthe dans le terminal
 * 
 */


#include "../include/maze.hpp"
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

