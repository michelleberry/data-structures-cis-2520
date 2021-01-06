#include <stdlib.h>
#include <stdio.h>
#include "array.h"
 
struct Performance *newPerformance(){
    struct Performance *new; 
    new = malloc(sizeof(struct Performance)); 
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

struct Array *newArray( struct Performance *performance, unsigned int width, unsigned int capacity ){
    struct Array *new; 
    new = malloc(sizeof(struct Array)); 
    if( new == NULL ){
        fprintf(stderr, "Array: malloc failed. Program exiting.\n"); 
        exit(1); 
    }
    new->width = width; 
    new->nel = 0; 
    new->capacity = capacity; 
    new->data = malloc(width*capacity);
    if( new->data == NULL ){
        fprintf(stderr, "Array: malloc failed. Program exiting.\n"); 
        exit(1); 
    }
    performance->mallocs++; 
    return new;  
}

void readItem( struct Performance *performance, struct Array *array, unsigned int index, void *dest ){
    if( index >= array->nel){
        fprintf(stderr, "readItem: invalid index. Program exiting\n"); 
        exit(1); 
    }

    int i; int j = 0; 
    unsigned char *cdata = array->data;
    unsigned char *cdest = dest; 

    for(i = (index*(array->width)); i < ((index*(array->width)) + (array->width)); i++){
        cdest[j] = cdata[i]; 
        j++; 
    }

    performance->reads++; 
} 

void writeItem( struct Performance *performance, struct Array *array, unsigned int index, void *src ){
     if( index > array->nel || index == array->capacity ){
        fprintf(stderr, "writeItem: invalid index. Program exiting\n"); 
        exit(1); 
    }

    int i; int j = 0; 
    unsigned char *cdata = array->data;
    unsigned char *csrc = src; 

    if(index == array->nel){
        array->nel++; 
    }

    for(i = (index*(array->width)); i < ((index*(array->width)) + (array->width)); i++){
        cdata[i] = csrc[j]; 
        j++; 
    }

    performance->writes++; 
}

void contract( struct Performance *performance, struct Array *array ){
    if(array->nel == 0){
        fprintf(stderr, "contract: array already empty\n");
        exit(1); 
    }
    array->nel--; 
}

void freeArray( struct Performance *performance, struct Array *array ){
    free(array->data); 
    free(array); 
    performance->frees++; 
}

void appendItem( struct Performance *performance, struct Array *array, void *src ){
    writeItem(performance, array, array->nel, src); 
}

void insertItem( struct Performance *performance, struct Array *array, unsigned int index, void *src ){
    void *dts = malloc(array->width);  //data to shift
    int i; 
    for(i = (array->nel); i > (index); i--){   
        //read i-1 and move to i
        readItem(performance, array, i-1, dts);
        writeItem(performance, array, i, dts); 
    }
    //write the new data (1 piece / 1 width) at index
    writeItem(performance, array, index, src); 
    free(dts); 
}

void prependItem( struct Performance *performance, struct Array *array, void *src ){
    insertItem(performance, array, 0, src); 
}

void deleteItem( struct Performance *performance, struct Array *array, unsigned int index ){
    void *dts = malloc(array->width); //data to shift
    int i; 
    for(i = index+1; i < (array->nel); i++){
        //read i and move to i-1 ( cover up index )
        readItem(performance, array, i, dts);
        writeItem(performance, array, i-1, dts); 
    }
    //remove last entry
    contract(performance, array); 
    free(dts); 
}

//linear search
int findItem( struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *), void *target ){
    int i = 0; 
    void *toCompare = malloc(array->width); 
    for( i = 0; i < array->nel; i++){
        readItem(performance, array, i, toCompare); 
        if( compar( target, toCompare) == 0){
            free(toCompare);
            return i; 
        }
    }
    free(toCompare);
    return -1; 
}

//binary search
//citation: code based on binary search section in zybook textbook ( section 2.2 ): https://learn.zybooks.com/zybook/UOGUELPHCIS2520KremerFall2020/chapter/2/section/2 
int searchItem( struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *), void *target ){
    int hi = (array->nel) - 1; 
    int mid = 0;
    int low = 0;
    void *toCompare = malloc(array->width); 

    //loop to binary search
    while( hi >= low){
        mid = (hi + low) /2; 
        readItem(performance, array, mid, toCompare); 
        //if higher, continue searching higher portion of array
        if( compar(target,toCompare) > 0){
            low = mid + 1; 
        //if lower, continue searching lower portion of array
        } else if( compar(target, toCompare) < 0){
            hi = mid - 1; 
        //else must == 0, so return index of target in array
        } else {
            free(toCompare); 
            return mid; 
        }
    } 

    //if not found in search, return -1
    free(toCompare); 
    return -1; 
}
