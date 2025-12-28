<<<<<<< HEAD
cmake_minimum_required(VERSION 3.15)

project(MazeViewer VERSION 1.0 LANGUAGES CXX)
=======
cmake_minimum_required(VERSION 3.16)
project(Catch2Examples LANGUAGES CXX)

list(APPEND CMAKE_PREFIX_PATH "~/local/install_catch2")
find_package(Catch2 3 REQUIRED)

add_executable(test test/test.cpp)
target_link_libraries(test PRIVATE Catch2::Catch2WithMain)
cmake_minimum_required(VERSION 4.1.2)
project(MazeSolver)
>>>>>>> 535c780 (Petites Modifs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
<<<<<<< HEAD

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# --- Executable 1: maze_sfml ---
add_executable(maze_sfml
    src/SFML_TB.cpp
    src/maze_TB.cpp
    src/solver_TB.cpp
)

target_link_libraries(maze_sfml PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

# --- Executable 2: maze_game ---
add_executable(maze_game
	src/SFML_game.cpp
	src/maze_TB.cpp
	src/solver_TB.cpp
)

target_link_libraries(maze_game PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

# ================================
#           TESTS
# ================================
include(CTest)

# Tell CMake where Catch2 is installed
set(CMAKE_PREFIX_PATH "/usr/local/opt/catch2" ${CMAKE_PREFIX_PATH})

find_package(Catch2 3 REQUIRED)

add_executable(tests
    tests/test_solver.cpp
    src/solver_TB.cpp
    src/maze_TB.cpp
)

target_compile_definitions(tests PRIVATE UNIT_TEST)

target_link_libraries(tests PRIVATE
    Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(tests)
=======
add_library(maze src/main.cpp)

