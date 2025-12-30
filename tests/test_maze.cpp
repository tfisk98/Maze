#define CATCH_CONFIG_MAIN
#include<catch2/catch_test_macros.hpp>
#include "maze.hpp"
#include <vector>


TEST_CASE ("fonction inBounds fonctionne","[inBounds]"){
    
    Maze m(2,3);
    
    REQUIRE(m.inBounds(2,3)==false);
    
    REQUIRE(m.inBounds(1,3)==false);
    
    REQUIRE(m.inBounds(2,2) == false);
    
    REQUIRE(m.inBounds(0,0)==true);
}
