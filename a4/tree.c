#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree.h"

//if tree is empty, return 1. otherwise return 0. do not modify performance
int isEmpty( struct Performance *performance, struct Node **node_ptr ){
    if(*node_ptr == NULL){
        return 1; 
    }
    return 0; 
}

struct Performance *newPerformance(){
    struct Performance *new; 
    new = (struct Performance *)malloc(sizeof(struct Performance)); 
    if( new == NULL ){
        fprintf(stderr, "Performance: malloc failed. Program exiting.\n"); 
        exit(1); 
    }
    new->reads = 0; 
    new->writes = 0; 
    new->mallocs = 0; 
    new->frees = 0; 
    return new; 
}

void attachNode( struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width ){
    struct Node *new = (struct Node *)malloc( sizeof( struct Node ));
    new->data = malloc(width); 

    //check for error conditions if mallocs failed 
    if( new == NULL || new->data == NULL){
        fprintf(stderr, "attachNode: malloc failed. Program exiting.\n"); 
        exit(1); 
    }
    memcpy(new->data, src, width);               //copy width bytes from src into newnode->data
    new->lt = NULL;                              //set less than ptr to null
    new->gte = NULL;                             //set greater than or equal ptr to null
    *node_ptr = new;                           //copy address of new into node_ptr

    performance->mallocs++;                      //update performance
    performance->writes++;  
}

int comparNode( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target ){
    performance->reads++; 
    return compar(target, (*node_ptr)->data); 
}

struct Node **next( struct Performance *performance, struct Node **node_ptr, int direction ){
    //check for error condition if tree empty
    if(isEmpty(performance,node_ptr)){
        fprintf(stderr, "next: Error: tree empty. Program exiting.\n");
        exit(1); 
    } 
    performance->reads++; 
    if(direction < 0){
        return &((*node_ptr)->lt);
    }
    return &((*node_ptr)->gte);
}

void readNode( struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width ){
    //check for error condition if tree empty 
    if(isEmpty(performance,node_ptr)){
        fprintf(stderr, "readNode: Error: tree empty. Program exiting.\n");
        exit(1); 
    }
    
    performance->reads++; 
    memcpy(dest, (*node_ptr)->data, width);
}

//free node structure that used to be in the tree, pointed to by node_ptr
void detachNode( struct Performance *performance, struct Node **node_ptr ){
    //check for error condition if tree empty 
    if(isEmpty(performance,node_ptr)){
        fprintf(stderr, "detachNode: Error: tree empty. Program exiting.\n");
        exit(1); 
    }
 
    free((*node_ptr)->data);
    free((*node_ptr)); 
    *node_ptr = NULL; 

    performance->frees++; 
}

//add an item to its appropriate place in the tree
void addItem( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *src, unsigned int width ){
    if(isEmpty(performance,node_ptr)){                   //when there is no more nodes to traverse
        attachNode(performance, node_ptr, src, width);   //attach node as a leaf
    } else {
        int direction = comparNode( performance,node_ptr,compar,src );                     //find direction we should move new data into
        addItem(performance, next(performance, node_ptr, direction) , compar, src, width); //call function again with next node in according direction
    }
}

//free tree recursively 
void freeTree( struct Performance *performance, struct Node **node_ptr ){
    if(isEmpty(performance, node_ptr) == 0){                    //stop when node is empty to prevent seg faulting
        freeTree( performance, next(performance,node_ptr,1) );
        freeTree( performance, next(performance,node_ptr,-1) );
        detachNode(performance, node_ptr);  
    }
}

//search binary search tree
int searchItem( struct Performance *performance, struct Node **node_ptr, int(*compar)(const void *, const void *), void *target, unsigned int width){
    if(isEmpty(performance,node_ptr)){   //if node is empty, return 0
        return 0;  
    }

    int direction = comparNode(performance, node_ptr, compar, target); //perform comparison
    if(direction == 0){                                                //if desired node has been found
        readNode(performance, node_ptr,target,width);                  //read data into target
        return 1;                                                      //return
    }
    
    return searchItem(performance, next(performance, node_ptr, direction), compar, target, width); 
}
