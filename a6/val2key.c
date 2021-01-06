#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "hashfn.h"

FILE * init_filepointer(char *filename, char* mode);
void val2key( FILE *KVP, FILE *VHSP, char *searchTerm, char *readKey);

//accepts 2 cmd line arguments: filename and 'search term'
int main(int argc, char **argv){
    if(argc != 3){
        fprintf( stderr, "Usage: %s filename.kv 'search term'\n", argv[0]);
        exit(0); 
    } // else
    char filename[STRLEN];
    strcpy(filename, argv[1]);    //we may assume this file exists/is a valid file name
    char searchTerm[STRLEN];
    strcpy(searchTerm, argv[2]);

    int n = strcspn(filename, "kv"); 
    char vhsfilename[STRLEN] = ""; 
    strncpy(vhsfilename, filename, n);
    strcat(vhsfilename, "vhs");

    //initialize .kv file pointer for reading 
    FILE *KVP = init_filepointer(filename, "r"); 
    //initialize .vhs file pointer for reading
    FILE *VHSP = init_filepointer(vhsfilename, "r"); 

    char readKey[STRLEN] = "";
    val2key(KVP, VHSP, searchTerm, readKey);

    if(strcmp(readKey, "") == 0){
        printf("NOT FOUND\n"); 
    }else{
       printf("%s\n", readKey);
    }

    fclose(KVP); 
    fclose(VHSP); 
    
}

void val2key( FILE *KVP, FILE *VHSP, char *searchTerm, char *readKey){
    int readIndex = 0; 
    char readVal[STRLEN] = ""; 
    int cap = get_capacity(VHSP);
    int hashval = hashfn(searchTerm, cap);
    int j = 0;
    //search for key's value   
    read_index(VHSP, hashval, &readIndex);
    while(j < cap && readIndex != -1){ //how to check if key null?
        read_val(KVP, readIndex, readVal);
        if(strcmp(readVal, searchTerm) == 0){
           read_key(KVP, readIndex, readKey); 
           return;
        }
        hashval++; j++; 
        if(hashval == cap){
            hashval = 0; 
        } 
        read_index(VHSP, hashval, &readIndex);
    }
}

FILE * init_filepointer(char *filename, char* mode){
    FILE *FP; 
    if((FP = fopen(filename, mode)) == NULL){
        printf("%s could not be opened\n", filename);
        exit(1); 
    }
    return FP; 
}