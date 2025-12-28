#ifndef CELL_H
#define CELL_H


/**
 * \file cell.hpp
 * \brief Classe Cell
 * \author Thomas Burns & Thomas Fisk
 * \version 0.1
 * \date 23/12/2025
 *
 * Contient l'objet cellule, "case" du labyrinthe,  utilisé pour générer et résoudre le labyrinthe.
 *
 */

#include <iostream>

struct Cell {
    char left; 
    char bot; 
    bool visited;
};

static Cell empty_cell = {' ', ' ', false};
static Cell full_cell  = {'|', '_', false};

#endif

