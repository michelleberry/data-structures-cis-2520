#include "ttt.h"
#include <stdio.h>
// call init_boards(), init_board(START_BOARD), and join_graph(START_BOARD)
// then, count the number of entries in the htable that have init==1
// this is nodes that can actually occur in real tic-tac-toe games.

int main(int argc, char **argv){
    init_boards(); 
    init_board(START_BOARD); 
    join_graph(START_BOARD);  
    int count = 0; 
    for(int i = 0; i < HSIZE; i++){
        if(htable[i].init == 1){ 
            count++; 
        }
    }
    printf("%d\n", count); 
}