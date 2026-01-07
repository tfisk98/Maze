#ifndef SOLVER_H
#define SOLVER_H

/**
 * \file solver.hpp
 * \brief Classe Solver
 * \author Thomas Burns & Thomas Fisk
 * \version 0.1
 * \date 23/12/2025
 *
 * Contient la classe solver qui gère la résolution du labyrinthe.
 * 
 */

#include "maze.hpp"
#include <vector>
#include <utility>


/**
* \class Solver
* \brief classe representant le solver, le résoluteur
*
*  La classe gere la résolution du labrinthe a travers l'algorithme AStar et/ou l'algorithme Trémaux.
*
*/

class Solver {
    
public:

    /**
     * \fn Solver(const Maze& m)
     * \brief Constructeur de la classe Solveur
     *
     * Apparie le solveur avec un labyrinthe
     *
     *\param une réference à un labyrinthe
     *\return objet de la classe Solveur
     */
    Solver(const Maze& m);

    /**
     * \fn std::vector<std::pair<int,int>>  solveAStar();
     * \brief Calcul du plus court chemin du labyrinthe avec l'algorithme AStar.
     *
     *  L'algorithme AStar est un algorithme de tyoe backtracking permettant une résolution exhaustive du problème
     *  de trouver le plus court chemin dans un labyrinthe.
     *
     * \param aucun
     * \return Vecteur de coordonnées des cellules parcourus par le plus court chemin chemin.
     */
    std::vector<std::pair<int,int>> solveAStar();

    /**
     * \fn std::vector<std::pair<int,int>>  solveAStar();
     * \brief Calcul du plus court chemin du labyrinthe avec l'algorithme Tremaux.
     *
     *
     *
     * \param aucun
     * \return Vecteur de coordonnées des cellules parcourus par le plus court chemin chemin.
     */
    std::vector<std::pair<int,int>> solveTremaux();

    
private:
    const Maze& maze;
    int nr, nc;

   
    /**
     * \fn bool canMove(int r1, int c1, int r2, int c2) ;
     * \brief Verifie qu'aller du point de coordonner(r1,c1) au point (r2,c2) est possible.
     *
     * Regarde si (r2,c2) est toujours dans les limites du labyrinthes.
     * Si oui, vérifie qu'un mur ne se trouve pas entre (r1,c1) et (r2,c2).
     * Renvois False si c'est le cas, True sinon
     *
     * \param la ligne r1 et la colonne c1 du point de coordonnée actuel et la ligne r2 et la colonne c2 du point vers lequel on veut aller.
     * \return True(1) si c'est possible, False(0) sinon.
     */
    bool canMove(int r1, int c1, int r2, int c2) const;

    /**
     *\fn int manhattan(int r, int c);
     * \brief Calcul du plus court chemin du labyrinthe avec l'algorithme AStar.
     *
     *  Calcule la distance d'un point (r,c) au point de sortie du labyrinthe.
     *
     * \param aucun
     * \return Vecteur de coordonnées des cellules parcourus par le plus court chemin chemin.
     */
    int manhattan(int r, int c) const;

public:    
    int a = 6;

	int manhattanPublic(int r, int c) const {
        return manhattan(r, c);
    }
    
    bool canMovePublic(int r1, int c1, int r2, int c2) const{
        return canMove(r1,c1,r2,c2);
    }
	
};

#endif

