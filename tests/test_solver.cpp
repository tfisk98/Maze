#define CATCH_CONFIG_MAIN
#include<catch2/catch_test_macros.hpp>
#include "solver.hpp"
#include "maze.hpp"
#include <vector>

TEST_CASE ("fonction heuristique (manhattan) fonctionne ", "[manhattan]") {

	Maze m(5,5);
	Solver s(m);

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


/*
TEST_CASE ("algorithme A* fonctionne", "[algorithme A*]"){

	Maze m(5,5);
	Solver s(m);
	std::vector<std::pair<int,int>> path = s.solveAStar();
	
	REQUIRE((path[0].first, path[0].second) = m.cols() && (path[4].first, path[4].second) = m.rows());
}
*/
