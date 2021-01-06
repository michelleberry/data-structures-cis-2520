#ifndef ARRAY_H
#define ARRAY_H

struct Array{
    unsigned int width;      //size in bytes of each elem in array
    unsigned int nel;        //number of elements in array
    unsigned int capacity;   //total number of elements that can be stored in the array
    void *data;              //pointer to the contents of the array
}; 

struct Performance{
    unsigned int reads; 
    unsigned int writes; 
    unsigned int mallocs; 
    unsigned int frees; 
}; 

struct Performance *newPerformance(); 
//create new Performance structure

struct Array *newArray( struct Performance *performance, unsigned int width, unsigned int capacity ); 
//create new Array structure, set attributes

void readItem( struct Performance *performance, struct Array *array, unsigned int index, void *dest ); 
//copy array->width bytes from array->data (offset by the index) to *dest memeory address, and update performance

void writeItem( struct Performance *performance, struct Array *array, unsigned int index, void *src ); 
//copy array->width bytes from memory address at src to the memory address array->data offset by index (x array->width), and update performance

void contract( struct Performance *performance, struct Array *array );
//decrement array->nel by one

void freeArray( struct Performance *performance, struct Array *array );
//free array->data and the structure itself, and update performance ( add one frees )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////** DERIVED FUNCTION PROTOTYPES : Implement those below by calling those above **///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void appendItem( struct Performance *performance, struct Array *array, void *src ); 

void insertItem( struct Performance *performance, struct Array *array, unsigned int index, void *src );
//use readItem and writeITem calls to move all the elements in the array at index and over by 1, and then write given data (src) at index in the array

void prependItem( struct Performance *performance, struct Array *array, void *src ); 
//use insertItem to insert data at position 0 (opposite of append)

void deleteItem( struct Performance *performance, struct Array *array, unsigned int index );
//use readItem and writeItem calls to move all elements in the array at the position given by index+1 and higher back one, and then use contract to remove duplicate last entry

//////////////////////////////////////////////////////////The Last 20%////////////////////////////////////////////////////////////////////////////

int findItem( struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *), void *target );

int searchItem( struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *), void *target ); 

#endif