#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

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

//prepend a node to the list
void push( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ){
    struct Node *new = (struct Node *)malloc( sizeof( struct Node ));
    new->data = malloc(width);                                            //malloc a new node

    //check for error conditions if mallocs failed 
    if( new == NULL || new->data == NULL){
        fprintf(stderr, "Push: malloc failed. Program exiting.\n"); 
        exit(1); 
    }

    memcpy(new->data, src, width);               //copy width bytes from src into newnode->data
    new->next = *list_ptr;                       //set next pointer to be equal to the value pointed to by list_ptr
    *list_ptr = new;                             //store address of new in pointer that is pointed to by list_ptr   

    performance->mallocs++;                      //update performance
    performance->writes++;                      
}

//read head of list (peek)
void readHead( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ){
    //check for error condition if list empty 
    if(isEmpty(performance,list_ptr)){
        fprintf(stderr, "readHead: Error: list empty. Program exiting.\n");
        exit(1); 
    }

    memcpy(dest, (*list_ptr)->data, width);
    performance->reads++; 
}

//pop: remove first item in list (head)
void pop( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ){
    //check for error condition if list empty
    if(isEmpty(performance,list_ptr)){
        fprintf(stderr, "pop: Error: list empty. Program exiting.\n");
        exit(1); 
    } 
    struct Node *remove = *list_ptr;                  //point to node to remove
    memcpy(dest, remove->data, width);                //copy bytes to dest
    *list_ptr = remove->next;                         //update list_ptr to the next node in list after the remove node
    
    free(remove->data);             
    free(remove); 
                
    performance->frees++;
    performance->reads++; 
}

//return ptr to the pointer to the second item in a list
struct Node **next( struct Performance *performance, struct Node **list_ptr ){
    //check for error condition if list empty
    if(isEmpty(performance,list_ptr)){
        fprintf(stderr, "next: Error: list empty. Program exiting.\n");
        exit(1); 
    } 
    performance->reads++; 
    return &((*list_ptr)->next);     //otherwise return address of next node
} 

//if list is empty, return 1. otherwise return 0. do not modify performance
int isEmpty( struct Performance *performance, struct Node **list_ptr ){
    if(*list_ptr == NULL){
        return 1; 
    }
    return 0; 
}

//pop until list empty
void freeList( struct Performance *performance, struct Node **list_ptr ){
    int destination;                            
    while(isEmpty(performance,list_ptr)==0){ 
        pop(performance, list_ptr, &destination, 0);
    }
}

//use next and readHead functions to find Node i to retrieve data from the given position in the list
void readItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width ){
    int j = 0; 
    for( j = 0; j < index; j++ ){
        list_ptr = next(performance, list_ptr);  
    }
    readHead(performance, list_ptr, dest, width); 
}

//call next until isEmpty returns true then call push to add item at end of list
void appendItem( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ){
    while(isEmpty(performance, list_ptr) == 0){
        list_ptr = next(performance, list_ptr);
    }
    push(performance,list_ptr,src,width); 
} 

//insert item at index 
void insertItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width ){
    int j = 0; 
    for( j = 0; j < index; j++ ){               //move list ptr to location of index node
        list_ptr = next(performance, list_ptr);  
    }
    push(performance,list_ptr,src,width);       //push to list 
} 

//insert item at index 0
void prependItem( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ){
    insertItem(performance,list_ptr,0,src,width); 
} 

//use next and pop calls to remove node at given index
void deleteItem( struct Performance *performance, struct Node **list_ptr, unsigned int index ){
    int j = 0; 
    for( j = 0; j < index; j++ ){
        list_ptr = next(performance, list_ptr);  
    }
    pop(performance, list_ptr, &j, 0); 
}

//find index of given item and return index, returning -1 if not found in list
int findItem( struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width ){
    void *temp = malloc(width);
    int i = 0;  
    //while list is not empty
    while(isEmpty(performance,list_ptr) == 0){      
        readHead(performance, list_ptr, temp, width);       //read head
        if(compar(target,temp) == 0){                       //compare head to target
            free(temp);                                     //if they are equal, free temp and return index
            return i;  
        } 
        list_ptr = next(performance, list_ptr);             //advance list_ptr to next node
        i++;  
    }
    free(temp);
    return -1; 
}

