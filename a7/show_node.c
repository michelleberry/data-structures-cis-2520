#include "ttt.h"
#include <stdlib.h>
#include <stdio.h>
//accepts 0 or more integer command line arguments, it will display the value of the board node corresponding to the cmd line args.

int main( int argc, char **argv ){
    //call init_boards(), init board(START_BOARD), join_graph(START_BOARD), and compute_score()
    init_boards(); 
    init_board(START_BOARD); 
    join_graph(START_BOARD); 
    compute_score(); 
    //then for each cmd line arg it will call print_node() on the location in the htable corresponding to the cmd line arg
    for(int i=1; i < argc; i++){
        struct BoardNode to_print = htable[atoi(argv[i])]; 
        print_node(to_print); 
    }
}