#include <iostream>
#include <vector>
#include <random>

#include "maze.h"


char select (char c, int d){
    return (rand() % 100 < d) ? ' ' : c ;
}

Cell Maze::operator()(const std::size_t& j,
                const std::size_t& k){
    return data[j*nc+k];
}

const Cell Maze::operator()(const std::size_t& j,
                            const std::size_t& k) const
{
    return data[j*nc+k];
}

std::tuple<std::vector<std::tuple<std::size_t, std::size_t> >, int> Maze::gen_path(std::tuple<size_t, size_t> origin){
    
    // origin and goal
    //std::tuple<size_t, size_t> origin = std::make_tuple(0,0);
    std::tuple<size_t, size_t> goal = std::make_tuple(nr,nc);
    std::vector<std::tuple<std::size_t, std::size_t>>       path;
    path.reserve(nr*nc);
    
    //std::tuple<size_t, size_t> curr_cell = origin;
    
    // start row and start col
    std::size_t curr_row = std::get<0>(origin);
    std::size_t curr_col = std::get<1>(origin);
    
    int seed = 42;
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> unif(1,4);
    
    int len = 1;
    bool new_pt = false;
    
    while( curr_row < nr and curr_col < nc ){
        int depl_index = unif(gen);
        if (depl_index == 1){
            if (not data[curr_row*nc + curr_col -1].visited ){
                curr_col -= 1;
                new_pt = true;
                
            }
        }
        else if(depl_index == 2){
            if (not data[curr_row*nc + curr_col+1].visited ){
                curr_col += 1;
                new_pt = true;
            }
        }
        else if(depl_index == 3){
            if (not data[(curr_row-1)*nc + curr_col].visited ){
                curr_row -= 1;
                new_pt = true;
            }
        }
        else {
            if (not data[(curr_row-1)*nc + curr_col].visited ){
                curr_row += 1;
                new_pt = true;
            }
        }
        
        if (new_pt){
            data[curr_row*nc + curr_col].visited = true;
            path.push_back(std::make_tuple(curr_row,curr_col));
            len += 1;
            new_pt = false;
        }
        
        
        
    }
    
    std::tuple<std::vector<std::tuple<std::size_t, std::size_t> >, int> response = {path , len};
    return response ;
    
}

void Maze::generate(){
    int wall_count = 0;
    //Top of the maze
    for(std::size_t col= 0 ; col < nc; col ++){
        data[col].left = ' ';
    }
    data[nc-1].bot = ' ';
    
    /// Core of the Maze
    for(std::size_t row = 1; row < nr -1 ; row ++){
        data[row*nc].bot = select('_',walls_prct);
        if(data[row*nc].bot == '_'){
            wall_count ++;
        }
        for(std::size_t col = 1 ; col < nc-1; col ++){
            if(wall_count < wall_nb){
                data[row*nc + col].left = select('|',walls_prct);
                data[row*nc + col].bot = select('_',walls_prct);
                if(data[row*nc + col].left == '|'){
                    wall_count ++;
                }
                if(data[row*nc + col].bot == '_'){
                    wall_count ++;
                }
            }
        }
        data[row*nc + nc-1].bot = ' ';
    }
    
    ///Bottom of the maze
    for(std::size_t col=1 ; col < nc-1; col ++){
        data[nr*(nc - 1) + col].left = select('|',walls_prct);
        if(data[nr*(nc - 1) + col].left == '|'){
            wall_count ++;
        }
    }
    
    data[nr*nc -2].bot = ' ';
    data[nr*nc -1].bot = ' ';
    
    
}

void Maze::print(){
    for(std::size_t row = 0; row < nr; row ++){
        for(std::size_t col =0; col < nc; col ++){
            std::cout<<data[row*nc + col].left << data[row*nc + col].bot;
        }
        std::cout<<std::endl;
    }
}


