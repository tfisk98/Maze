#define CATCH_CONFIG_MAIN
#include<catch2/catch_test_macros.hpp>
#include "solver_TB.hpp"
#include "maze.hpp"

TEST_CASE ("fonction heuristique (manhattan) fonctionne ", "[heuristic]") {

	Maze m(5,5);
	Solver s(m);

	REQUIRE(s.heuristic_public(1,1) == 6);
}


