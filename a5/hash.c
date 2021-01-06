#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

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

struct HashTable *createTable(struct Performance *performance, unsigned int capacity, int (*hash)(void *, int), int(*compar)(const void *, const void *)){
    struct HashTable *newTable = (struct HashTable *) malloc (sizeof(struct HashTable));
    newTable->data = malloc(sizeof(void*) * capacity); 

    //check for error conditions if mallocs failed 
    if( newTable == NULL || newTable->data == NULL){
        fprintf(stderr, "createTable: malloc failed. Program exiting.\n"); 
        exit(1); 
    }

    for(int i=0; i<capacity; i++){
        newTable->data[i] = NULL; 
        performance->reads++; 
    }

    newTable->capacity = capacity; 
    newTable->nel = 0; 
    newTable->compar = compar; 
    newTable->hash = hash; 

    performance->mallocs++; 
    return newTable; 
}

void addElement( struct Performance *performance, struct HashTable *table, void *src){
    //check for error conditions if table full
    if( table->nel == table->capacity ){
        fprintf(stderr, "addElement: table full. Program exiting.\n"); 
        exit(1); 
    }

    int i = table->hash(src, table->capacity);            
    int j = 0; 

    //loop to handle collisions, if no collision, loop is never used 
    while(j < table->capacity && table->data[i] != NULL){
        performance->reads++;
        i++; j++; 
        if(i == (table->capacity)){ //IF the index reaches capacity in table, it should be set to zero instead (loop/wrap arounD)
            i = 0;                                  
        }
    }

    table->data[i] = src;   //copy pointer value of src to the index in the array  
    table->nel++; 
    performance->writes++;
    //printf("%d placed at %d\n", table->hash(src, table->capacity), i);
}

int getIdx( struct Performance *performance, struct HashTable *table, void *src ){
    int hypoIndex = table->hash(src, table->capacity);
    int i = 0; int j = 0;

    for(i = hypoIndex, j = 0; j < table->capacity; i++, j++){
        if(i == table->capacity){
            i = 0; 
        }
        if(table->data[i] != NULL){
            performance->reads++;
            if(table->compar(table->data[i], src) == 0){  //if there is a match
                return i; 
            }
        } 
    }

    return -1; 
}

//free the data array as well as the HashTable structure
void freeTable( struct Performance *performance, struct HashTable *table ){
    free(table->data); 
    free(table); 
    performance->frees++; 
}

//return element of a target 
void *getElement( struct Performance *performance, struct HashTable *table, void *src){
    int index = getIdx(performance, table, src); 
    if(index != -1){
        return table->data[index]; 
    }
    return NULL; 
}

//search for target element and remove, setting old index to null 
void removeElement( struct Performance *performance, struct HashTable *table, void *target ){
    int idx = getIdx(performance, table, target); 
    table->data[idx] = NULL; 
    performance->writes++; 
    table->nel--; 
}

//returns the # spaces between a data spot's index and it's hash value
int calcDifference( int index, int hash, int capacity){
    if( index < hash ){
        return (index + (capacity - hash)); 
    } else {
        return (index - hash); 
    }
}

//checks accuracy of hashtable (i.e. total differences btw hash index and hash value)
int hashAccuracy( struct HashTable *table ){
    int hash; 
    int hashAccuracy = 0; 
    for(int i = 0; i < table->capacity; i++){
        if(table->data[i] != NULL){
            hash = table->hash(table->data[i], table->capacity);
            hashAccuracy += calcDifference(i, hash, table->capacity); 
        }
        
    }
    return hashAccuracy; 
}

//adjust hashtable to have lower hashAccuracy (less displaced nodes)
void rehash( struct HashTable *table ){
    int i = 0; int j = 0; int k = 0; 
    for(i = 0; i < table->capacity; i++){
        if(table->data[i] != NULL){
            int hashVal = table->hash(table->data[i], table->capacity);
            int difference = calcDifference(i, hashVal, table->capacity);
            //printf("hash: %d idx: %d diff:% d\n", table->hash(table->data[i], table->capacity), i, difference ); 
            if(difference > 0){
                for(j = hashVal, k = 0; k < difference; k++, j++){
                    if(j == table->capacity){
                        j = 0; 
                    }
                    if(table->data[j] == NULL){
                        table->data[j] = table->data[i]; 
                        table->data[i] = NULL; 
                    }
                } 
            } 
        }
    }
} 