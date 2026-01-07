cmake_minimum_required(VERSION 3.15)
project(MazeProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Paths ---
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)

# --- Common sources (shared code) ---
set(COMMON_SOURCES
    ${SRC_DIR}/maze.cpp
    ${SRC_DIR}/solver.cpp
)

# --- Include directories ---
# If your headers are in include/, this makes #include "maze.hpp" work cleanly.
include_directories(${INC_DIR})

# ------------------------------------------------------------
# 1) Terminal executable
# ------------------------------------------------------------
add_executable(maze_terminal
    ${SRC_DIR}/main.cpp
    ${COMMON_SOURCES}
)

# ------------------------------------------------------------
# 2) SFML executables
# ------------------------------------------------------------
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(sfml_game
    ${SRC_DIR}/SFML_game.cpp
    ${COMMON_SOURCES}
)

target_link_libraries(sfml_game PRIVATE SFML::Graphics SFML::Window SFML::System)

add_executable(sfml_window
    ${SRC_DIR}/SFML_orig.cpp
    ${COMMON_SOURCES}
)

target_link_libraries(sfml_window PRIVATE SFML::Graphics SFML::Window SFML::System)

# ------------------------------------------------------------
# Copy arial.ttf next to the sfml_game executable after build
# (so you can run it from the build directory)
# ------------------------------------------------------------
add_custom_command(TARGET sfml_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${ASSETS_DIR}/arial.ttf
            $<TARGET_FILE_DIR:sfml_game>/arial.ttf
    COMMENT "Copying arial.ttf next to sfml_game executable"
)

# ------------------------------------------------------------
# 3) Tests Autos
# ------------------------------------------------------------

list(APPEND CMAKE_PREFIX_PATH "~/local/install_catch2")
find_package(Catch2 3 REQUIRED)

enable_testing()

add_executable(tests
    tests/test_maze.cpp
    tests/test_solver.cpp
    src/maze.cpp
    src/solver.cpp
)

target_link_libraries(tests
    PRIVATE
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)

catch_discover_tests(tests)

add_custom_target(run_tests
    COMMAND ctest --output-on-failure
    DEPENDS tests
)

