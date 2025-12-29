#define CATCH_CONFIG_MAIN
#include<catch2/catch_test_macros.hpp>
#include "solver.hpp"
#include "maze.hpp"
#include<vector>

TEST_CASE ("fonction heuristique (manhattan) fonctionne ", "[manhattan]") {

	Maze m(5,5);
	Solver s(m);

	REQUIRE(s.manhattanPublic(1,1) == 6);
}

TEST_CASE ("fonction compte les"){
    int a = 2;
    REQUIRE(a==2);
}

/*
TEST_CASE ("algorithme A* fonctionne", "[algorithme A*]"){

	Maze m(5,5);
	Solver s(m);
	std::vector<std::pair<int,int>> path = s.solveAStar();
	
	REQUIRE((path[0].first, path[0].second) = m.cols() && (path[4].first, path[4].second) = m.rows());
}
*/
