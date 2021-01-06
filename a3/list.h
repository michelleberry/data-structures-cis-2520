#ifndef LIST_H
#define LIST_H

struct Node{
    void *data; 
    struct Node *next; 
}; 

struct Performance{
    unsigned int reads; 
    unsigned int writes; 
    unsigned int mallocs; 
    unsigned int frees;
};

struct Performance *newPerformance(); 

void push( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ); 
//add item containing *src data at head of the list

void readHead( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width );
//copy data from head of the list into *dest, if list empty print error to stderr and exit

void pop( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width );
//remove an item from the head of the list, if list empty print error to stderr and exit

struct Node **next( struct Performance *performance, struct Node **list_ptr ); 
//return ptr to the pointer to the second item in a list

int isEmpty( struct Performance *performance, struct Node **list_ptr ); 
//if list is empty, return 1. otherwise return 0. do not modify performance

//////////////////////////////////////////////////////////Derived Function Prototypes//////////////////////////////////////////////////////////////

void freeList( struct Performance *performance, struct Node **list_ptr ); 
//pop items off the list until the list isEmpty

void readItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width ); 
//use next and readHead functions to find Node i to retrieve data from the given position in the list

void appendItem( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ); 
//call next until isEmpty returns true then call push to add item at end of list

void insertItem( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width ); 

void prependItem( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ); 

void deleteItem( struct Performance *performance, struct Node **list_ptr, unsigned int index ); 
//use next and pop calls to remove node at given index

//////////////////////////////////////////////////////////The Last 20%//////////////////////////////////////////////////////////////

int findItem( struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width );
//linear search, return index if target found in list, otherwise return -1

#endif
