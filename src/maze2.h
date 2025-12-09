#ifndef MAZE_H
#define MAZE_H

#include "cell.h"

#include <iostream>
#include <vector>
#include <cassert>



/**
*       \class Maze
*
*       \brief class of maze object
*
*        This class generates a maze grid
*
*
*
*/



class Maze {
    
public:
    
 
    Maze(std::size_t nr0 = 0, std::size_t nc0 = 0, int nbw = 0, double wp = 0.): nr(nr0 + 1), nc(nc0 + 1), wall_nb(nbw), walls_prct(wp) {
        //assert(nc == v.size());
        //assert(nr > 1);
        //assert(nc > 1);
        //assert( nbw <= 2*nr*nc);
        //assert( wp >= 0 );
        //assert( wp <= 100);
        
        std::vector<Cell> datana(nr*nc, full_cell);
        data = datana;
        
        std::tuple<size_t, size_t> origin = std::make_tuple(0,0);
        std::vector<std::tuple<std::size_t, std::size_t>> path;
        path.reserve(nr*nc);
        
    }
    /** \fn Constructor object
     * \brief Assign
     *
     *
     *\param nr0 : number of cells per row in the visible maze, nc0: number of cells per column in the visible maze, nbw : maximum  number of walls to build,
     * wp: likelihood to build a wall
     *\return  Maze object
    */
    
    int Maze::get_col(); /** \fn int get_col();
    			  * \brief Returns nb of columns 
    			  *
    			  *
    			  * \param None 
    			  * \return nc 
    			  */							
    								

    int Maze::get_row(); /** \fn int get_row();
    			  * \brief Returns nb of rows
    			  *
    			  *
    			  *
    			  * \param None
    			  * \return nr
    			  */

    
    
    Cell
    operator()(const std::size_t& j,
               const std::size_t& k);
    
    
    /** \fn Cell operator (std::size_t& j, std::size_t k );.
     * \brief Returns the Cell object at coordinate (j, k);
     *
     *
     *
     *\param j : indice de ligne,  k indice de colonne
     *\return  Cell at coordinate (j,k)
    */
      
    const Cell
    operator()(const std::size_t& j,
               const std::size_t& k) const;
    
    /** \fn Cell operator (std::size_t& j, std::size_t k );.
     * \brief Returns the Cell object at coordinate (j, k);
     *
     *
     *
     *\param j : indice de ligne,  k indice de colonne
     *\return  const Cell at coordinate (j,k)
    */
    
    std::tuple<std::vector<std::tuple<std::size_t, std::size_t> >, int> gen_path(std::tuple<size_t, size_t> origin);
    /** \fn void gen_path ( ).
     * \brief builds a random path
     *
     * This functions starts from the starting cell and goes to the end in a randoim walk manner
     *
     *\param None
     *\return None
    */

    
    void generate();
        
        /** \fn void generate ( ).
         * \brief assembles the maze given mazeo object caracteristics : number of rows, number of columns, number of walls, probability of putting down a wall
         *
         * This function builds a maze represented as a big matrix of cells where each cell gets attributed a left and bottom woth probabily walls_prob
         *
         *\param None
         *\return None
        */
        
    void print();
    
    /** \fn void print( ).
     * \brief prints the maze to the terminal
     *
     * This function calls std::cout on each Cell.left and Cell.bot member
     *
     *\param None
     *\return None
    */
    
    
    private :
    
    typedef std::tuple<std::size_t,
               std::size_t,
               Cell>  CellContainer;/*!< Tuple contenant l'indice de ligne, colonne et l'objet Cellule du maillage */
    
    //typedef std::tuple<std::size_t, std::size_t> Coordinates;

    typedef std::vector<CellContainer> DataType; /*!< vector containing all generated Cell objects */
    
    const std::size_t             nr,nc; /*!< Number or rows, number of columns*/
    int                         wall_nb; /*!< Number of walls */
    double                    walls_prct; /*!< Probability of putting a wall down */
    std::vector<Cell>              data; /*!< Maze object*/
    //std::vector<Coordinates>       path;
    
    
    
    
};
    
#endif


/// Generation de la doc
///
/// Dossier test
///
/// //
