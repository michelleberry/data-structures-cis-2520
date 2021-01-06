#include "ttt.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// go through entire htable and set init variable in each structure to 0 (to indicate that element of the hash table is empty).
void init_boards(){
    for(int i = 0; i < HSIZE; i++){
        htable[i].init = 0; 
    }
} 

// return the number of markers (X's and O's ) on the board
int depth( Board board ){
    int markers = 0; 
    for(int i = 0; i < 9; i++){
        if(board[pos2idx[i]] == 'X' || board[pos2idx[i]] == 'O'){
            markers++; 
        }
    }
    return markers; 
}

// return 'X' if X has won, 'O' if O has won, '-' if game over and tied, '?' if not over and noone has won.
char winner( Board board ){
    //there will never be both 3xs and 3os in a board but
    if(htable[board_hash(board)].init == 1 && (htable[board_hash(board)].winner == 'O' || htable[board_hash(board)].winner == 'X')){
        return htable[board_hash(board)].winner; 
    }
    //loop thru WINS and check for each pattern
    for(int i=0; i<8; i++){ 
        if(board[pos2idx[WINS[i][0]]] == 'X' && board[pos2idx[WINS[i][1]]] == 'X' && board[pos2idx[WINS[i][2]]] == 'X'){
            return 'X'; 
        } else if(board[pos2idx[WINS[i][0]]] == 'O' && board[pos2idx[WINS[i][1]]] == 'O' && board[pos2idx[WINS[i][2]]] == 'O'){
            return 'O'; 
        }
    }

    if(depth(board) == 9){
        return '-'; 
    }

    return '?'; 
}

// return 'X' if it's X's turn, 'O' if it's O's turn, '-' if the game is over/board filled.
// use depth() and modular division to determine who's turn it is
char turn( Board board ){
    int dep = depth(board); 
    if(winner(board) != '?'){
        return '-'; 
    }else if(dep%2 == 1){
        return 'O'; 
    }
    return 'X'; //0%2 is 0
}

// compute the hash index of the provided board using board_hash() from ttt1.c
// set the variables of the structure @ that hash index as follows...
// init - 1, turn - return value of turn, depth - return value of depth, board - board argument (use strcpy), winner - return value of winner
void init_board( Board board ){
    int hash_idx = board_hash(board); 
    htable[hash_idx].init = 1; 
    htable[hash_idx].turn = turn(board); 
    htable[hash_idx].depth = depth(board); 
    strcpy(htable[hash_idx].board, board);
    htable[hash_idx].winner = winner(board);  
}

// create + join all the nodes of all possible tic-tac-toe games, can be done by looping over all possible move positions
void join_graph( Board board ){
    //recursive algorithm
    Board boardCopy; 
    //loop over all possible move positions
    for(int i = 0; i < 9; i++){
        //if there is not already a piece in this position
        if(board[pos2idx[i]] != 'X' && board[pos2idx[i]] != 'O'){
            //make a copy of the board
            strcpy(boardCopy, board); 
            //place appropriate marker in the copied board
            boardCopy[pos2idx[i]] = toupper(turn(board)); 
            //compute hash value of new board, and store it in the move array. 
            htable[board_hash(board)].move[i] = board_hash(boardCopy); 
            //if the entry at that hashindex is 0, 
            if(htable[board_hash(boardCopy)].init == 0){
                //recurisve 
                init_board(boardCopy); 
                join_graph(boardCopy);
            }  
        } else {
        //if there is already a piece in this position, store -1 in the move array
            htable[board_hash(board)].move[i] = -1; 
        }
    }

}

int getMaxChild( struct BoardNode node){
    int i = 8; int maxScore = -1; 
    while(i > -1){
        if(node.move[i] != -1 && htable[node.move[i]].score > maxScore){
            maxScore = htable[node.move[i]].score; 
        }
        i--; 
    }
    return maxScore; 
}

int getMinChild( struct BoardNode node){
    int i = 8; int minScore = 1; 
    while(i > -1){
        if(node.move[i] != -1 && htable[node.move[i]].score < minScore){
            minScore = htable[node.move[i]].score; 
        }
        i--; 
    }
    return minScore; 
}

// will assign a score to each entry in the htable that has an init value of 1
void compute_score(){ 
    for(int i = HSIZE-1 ; i > -1; i--){
        if(htable[i].init == 1){
            //assign a score//
            if(htable[i].winner == 'X'){
                htable[i].score = 1; 
            } else if(htable[i].winner == 'O'){
                htable[i].score = -1;
            } else if(htable[i].winner == '-'){
                htable[i].score = 0; 
            } else if(htable[i].winner == '?'){
                if(htable[i].turn == 'X'){
                    htable[i].score = getMaxChild(htable[i]); 
                } else if(htable[i].turn == 'O'){
                    htable[i].score = getMinChild(htable[i]); 
                }     
            }
        }
    }
}

// should return the best possible move position
// the best possible move position is the move leading to the child node w/ the highest score for X, and lowest score for O
int best_move( int board ){
    struct BoardNode node = htable[board]; 
    int hiScore;
    int toReturn;  
    if(node.turn == 'X'){
        hiScore = -2; 
        for(int i = 8; i > -1; i--){
            if(node.move[i] != -1 && htable[node.move[i]].score > hiScore ){
                hiScore = htable[node.move[i]].score;
                toReturn =  i; 
            }
        }
    } else if(node.turn == 'O'){
        hiScore = 2; 
        for(int j = 0; j < 9; j++){
            if(node.move[j] != -1 && htable[node.move[j]].score < hiScore){
                hiScore = htable[node.move[j]].score;
                toReturn = j; 
            }
        }
    } 
    return toReturn; 
}

