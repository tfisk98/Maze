cmake_minimum_required(VERSION 3.15)

# Project Name
project(MazeViewer VERSION 1.0 LANGUAGES CXX)

# 1. Set C++ Standard (-std=c++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Find SFML Package
# We look for SFML 3. If you installed it manually or via Homebrew/apt, 
# CMake should find the config files automatically.
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# 3. Create the Executable (-o maze_sfml)
# We include both source files here.
add_executable(maze_sfml SFML.cpp maze.cpp)

# 4. Link Libraries (-lsfml-graphics -lsfml-window -lsfml-system)
# SFML::Graphics automatically handles the -I includes and -L library paths for you.
target_link_libraries(maze_sfml PRIVATE SFML::Graphics SFML::Window SFML::System)
