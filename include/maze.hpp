#ifndef MAZE_H
#define MAZE_H


/**
 * \file maze.hpp
 * \brief Classe Maze 
 * \author Thomas Burns & Thomas Fisk
 * \version 0.1
 * \date 23/12/2025
 *
 * Contient la classe maze qui est l'objet labyrinthe.
 */

#include "cell.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <random>

/**
* \class Maze
* \brief classe representant le labyrinthe
*
*  La classe gere la génération et l'affichage du labyrinthe. Le labyrinthe est vue comme une matrice (nr,nc) ou un vecteur(nr.nc) de
*  cellules.
*  Elle renvoie le nombre de ligne du labyrinthe
*  Elle renvoie egalement le nombre de colonnes du labyrinthe
*  Elle vérifie que l'on reste dans les bornes du maillage
*/

class Maze {
public:
    Maze(std::size_t nr0 = 0, std::size_t nc0 = 0);

    Cell& operator()(const std::size_t &j, const std::size_t &k);
    const Cell& operator()(const std::size_t &j, const std::size_t &k) const;

    std::size_t rows() const {return nr; }
    std::size_t cols() const {return nc; }

    void generate();
    void print();

private:
    struct Wall {
        int r, c;
        char type; // 'L' or 'B'
    };

    bool in_bounds(int r, int c) const;

    std::size_t nr, nc;
    std::vector<Cell> data;
};


#endif

