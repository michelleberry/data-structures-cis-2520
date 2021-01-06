#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "hashfn.h"

void addElement( FILE *FP, int kvIndex, int capacity, int hashval); 
FILE * init_filepointer(char *filename, char* mode);

int main ( int argc, char **argv){
    //take 2 cmd line arguments
    if(argc != 3){
        fprintf( stderr, "Usage: %s filename.kv capacity\n", argv[0]); 
        exit(0); 
    } //else 
    char filename[STRLEN];
    strcpy(filename, argv[1]);    //we may assume this file exists/is a valid file name
    int capacity = atoi(argv[2]); 

    char key[STRLEN]; 
    char val[STRLEN]; 

    int n = strcspn(filename, "kv"); 
    char khsfilename[STRLEN] = ""; 
    char vhsfilename[STRLEN] = ""; 
    strncpy(khsfilename, filename, n);
    strncpy(vhsfilename, filename, n);
    strcat(khsfilename, "khs");
    strcat(vhsfilename, "vhs"); 

    //initialize .kv file pointer for reading
    FILE *KVP = init_filepointer(filename, "r"); 
    //initialize .khs file pointer for writing and reading
    FILE *KHSP = init_filepointer(khsfilename, "wb+");
    //intialize .vhs file pointer for writing and reading
    FILE *VHSP = init_filepointer(vhsfilename, "wb+"); 
    
    //initialize khs and vhs using: write_empty
    write_empty(KHSP, capacity); 
    write_empty(VHSP, capacity); 

    int index = 0; 
    //read contents of kv file using util library: read_keyval
    while(read_keyval(KVP, key, val) != 0){
        //printf("key: %s  value: %s\n", key, val);
        //write hash(key)/index and key to KHSP - account for linear probing
        addElement(KHSP, index, capacity, hashfn(key,capacity));
        //write hash(val)/index and val to VHSP - account for linear probing
        addElement(VHSP, index, capacity, hashfn(val, capacity));
        index++; 
    }
        
    fclose(KVP); 
    fclose(KHSP); 
    fclose(VHSP); 
}


//kv files: represent pairs of keys and values 
//khs files: key hash 
//vhs files: value hash

FILE * init_filepointer(char *filename, char* mode){
    FILE *FP; 
    if((FP = fopen(filename, mode)) == NULL){
        printf("%s could not be opened\n", filename);
        exit(1); 
    }
    return FP; 
}

//build hash table...use linear probing 
void addElement( FILE *FP, int kvIndex, int capacity, int hashval){
    int readIdx = 0; 
    int i = hashval;            
    int j = 0; 

    read_index(FP, i, &readIdx);
    //loop to handle collisions, if no collision, loop is never used 
    while(j < capacity && readIdx != -1){
        i++; j++; 
        if(j == capacity){ //program exits if there is no where to put the new value. ie, capacity was too small, but this should theoretically never happen.
            exit(1); 
        } else if(i == (capacity)){ //IF the index reaches capacity in table, it should be set to zero instead (loop/wrap arounD)
            i = 0;                                  
        }
        read_index(FP, i, &readIdx);
    }
    write_index(FP, kvIndex, i);  //write kv index to appropriate place in hash table  
}
