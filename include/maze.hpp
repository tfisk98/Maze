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

#include "cell.hpp"

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
    
    /**
     * \fn Maze(std::sizet nr0=0, std::sizet nc0=0);
     * \brief Construit un objet Labyrinthe de taille nr\*nc
     *
     * \param le nombre de ligne nr0 et le nombre de colonne nc0 du labyrinthe.
     * \return l'objet labyrinthe.
     */
    Maze(std::size_t nr0 = 0, std::size_t nc0 = 0);

    /**
     * \fn Cell& operator()(const std::sizet &j, const std::sizet &k );
     * \brief Renvoie la cellule a l'indice j,k de l'objet labyrinthe
     *
     * \param l'indice de ligne j et l'indice de colonne k du labyrinthe.
     * \return la cellule correspondante.
     */
    Cell& operator()(const std::size_t &j, const std::size_t &k);
    /**
     * \fn Cell& operator()(const std::sizet &j, const std::sizet &k );
     * \brief Renvoie la cellule a l'indice j,k de l'objet labyrinthe
     *
     * \param l'indice de ligne j et l'indice de colonne k du labyrinthe.
     * \return la cellule en version constante, correspondante.
     */
    const Cell& operator()(const std::size_t &j, const std::size_t &k) const;
    
    /**
     * \fn std::sizet rows()const ( );
     * \brief Renvoie le nombre de ligne du labyrinthe
     *
     * \param
     * \return nr, le nombre de ligne du labyrinthe
     */
    std::size_t rows() const {return nr; }
    
    
    /**
     * \fn std::sizet cols()const ( );
     * \brief Renvoie le nombre de ligne du labyrinthe
     *
     * \param
     * \return nc, le nombre de ligne du labyrinthe
     */
    std::size_t cols() const {return nc; }
    
    
    
    /**
     * \fn void generate( );
     * \brief génère le labyrinthe
     *
     * Dans un premier temps, génère un labyrinthe rempli. Chaque cellule est encerclée.
     * Passe sur chaque cellule à travers une marche aléatoire et y retire un mur au hasard, sans toucher aux murs extérieurs
     * au  labyrinthe. Possibilité d'un labyrinthe sans chemin ?
     * Puis repère les cellules correspondant à des impasses, y sélectionne un mur au hasard (gauche ou bas) et les stocke dans
     * un vecteur. Retire 20% des murs sélectionné. 100% donnerait un labyrinthe sans impasse.
     *
     * Retire le mur du bas de la première et de la dernière cellule pour garantir une entrée et une sortie.
     *
     */
    void generate();
    
    /**
     * \fn void print( );
     * \brief affiche le labyrinthe dans le terminal
     *
     * Parcours les céllules une à une.
     * Pour chaque cellule affiche "|" si il y a un mur à gauche de la cellule et un tiret du huit si le bas de la cellule est un mur.
     *
     */
    
    void print();
    
    /**
     * \fn bool inBounds(int r, int c) ;
     * \brief
     *
     * Regarde si (r,c) est toujours dans les limites du labyrinthes.
     * Renvois True si c'est le cas, False sinon
     *
     * \param la ligne r et la colonne c du point de coordonnée en question.
     * \return True(1) si c'est possible, False(0) sinon.
     */
    bool inBounds(int r, int c) const;

private:
    struct Wall {
        int r, c;
        char type; // 'L' or 'B'
    };

    std::size_t nr, nc;
    std::vector<Cell> data;
};


#endif

