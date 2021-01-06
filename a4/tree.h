
#ifndef TREE_H
#define TREE_H

struct Node{
    void *data;
    struct Node *lt;       //less-than child
    struct Node *gte;      //equal-or-greater-than child
};

struct Performance{
    unsigned int reads;
    unsigned int writes;
    unsigned int mallocs;
    unsigned int frees;
};

struct Performance *newPerformance();

void attachNode( struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width );

int comparNode( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target );

struct Node **next( struct Performance *performance, struct Node **node_ptr, int direction );

void readNode( struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width );

void detachNode( struct Performance *performance, struct Node **node_ptr );

int isEmpty( struct Performance *performance, struct Node **node_ptr );

//////////////////////////Derived Functions/////////////////////////////////////////

void addItem( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *src, unsigned int width );
//(Add an item to the tree at the appropriate spot.) 

void freeTree( struct Performance *performance, struct Node **node_ptr );

/////////////////////////Final 20%//////////////////////////////////////////////////

int searchItem( struct Performance *performance, struct Node **node_ptr, int(*compar)(const void *, const void *), void *target, unsigned int width);

#endif