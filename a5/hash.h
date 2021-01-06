#ifndef HASH_H
#define HASH_H

struct HashTable{
    unsigned int capacity;                   //number of elements in the table      
    unsigned int nel;                        //number of elements currently in the table
    void **data;                             //array of capacity number of pointers to the data accessed by hash table
    int (*hash)(void *, int);                //fn pointer to the hashing function / decides where to store the data
    int (*compar)(const void*, const void*); //fn pointer to fn which returns value of 0 if data stored at the 2 ptr arguments match
}; 

struct Performance{
    unsigned int reads;
    unsigned int writes;
    unsigned int mallocs;
    unsigned int frees;
};

struct Performance *newPerformance();

struct HashTable *createTable(struct Performance *performance, unsigned int capacity, int (*hash)(void *, int), int(*compar)(const void *, const void *));

//add an element to the hashtable, with linear probing when a collision occurs
void addElement( struct Performance *performance, struct HashTable *table, void *src);

int getIdx( struct Performance *performance, struct HashTable *table, void *src ); 

void freeTable( struct Performance *performance, struct HashTable *table ); 

void *getElement( struct Performance *performance, struct HashTable *table, void *src); 

void removeElement( struct Performance *performance, struct HashTable *table, void *target ); 

////////////////////////////////////the Last 20%////////////////////////////////////////////////

int hashAccuracy( struct HashTable *table ); 

void rehash( struct HashTable *table ); 

#endif