#define CATCH_CONFIG_MAIN
#include<catch2/catch_test_macros.hpp>
#include "solver.hpp"
#include "maze.hpp"
#include <vector>

TEST_CASE ("fonction heuristique (manhattan) fonctionne ", "[manhattan]") {

	Maze m(5,5);
	Solver s(m);
    

	//REQUIRE(s.a == 6);
    
    REQUIRE(s.manhattanPublic(1,1) == 6);
}


TEST_CASE ("fonction canMove fonctionne ", "[canMove]") {

    Maze m(5,5);
    Solver s(m);

    REQUIRE(s.canMovePublic(0,1,-1,1) == false);
    
    REQUIRE(s.canMovePublic(1,4,1,5) == false);
    
    REQUIRE(s.canMovePublic(2,3,2,2) == false);
    m(2,3).left = ' ';
    REQUIRE(s.canMovePublic(2,3,2,2) == true);
    
    m(1,2).bot = ' ';
    REQUIRE(s.canMovePublic(1,2,2,2)== true);
}



TEST_CASE ("algorithme A* fonctionne", "[algorithme A*]"){

	Maze m(5,5);
	Solver s(m);
	std::vector<std::pair<int,int>> path = s.solveAStar();
    
    std::pair<int,int> start = path.front();
    std::pair<int,int> goal = path.back();
	
    REQUIRE( start.first== 0 );
    REQUIRE( start.second == 0); // On débute bien en haut à gauche du labyrinthe
    REQUIRE( goal.first == m.rows()-1);
    REQUIRE( goal.second == m.cols() - 1); // On finit bien en bas à droite du labyrinthe
    
    unsigned int path_length = path.size();
    
    REQUIRE( path_length < m.rows()*m.cols()); // la longeueur du chemin est inférieur au nombre total de cellules
    
    //std::vector<std::pair<int, int>> tremaux = s.solveTremaux();
    
    //REQUIRE( path == tremaux );
    
    Maze m2(25,25);
    Solver s2(m2);
    path = s2.solveAStar();
    
    //std::pair<int,int> start = path.front();
    //std::pair<int,int> goal = path.back();
    
    //REQUIRE( start.first== 0 );
    //REQUIRE( start.second == 0); // On débute bien en haut à gauche du labyrinthe
    //REQUIRE( goal.first == m.rows()-1);
    //REQUIRE( goal.second == m.cols() - 1); // On finit bien en bas à droite du labyrinthe
    
    path_length = path.size();
    
    REQUIRE( path_length < m.rows()*m.cols());
    
}

