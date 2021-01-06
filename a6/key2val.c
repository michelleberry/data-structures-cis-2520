#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "hashfn.h"

FILE * init_filepointer(char *filename, char* mode);
void key2val( FILE *KVP, FILE *KHSP, char *searchTerm, char *readVal);

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
    char khsfilename[STRLEN] = ""; 
    strncpy(khsfilename, filename, n);
    strcat(khsfilename, "khs");

    //initialize .kv file pointer for reading 
    FILE *KVP = init_filepointer(filename, "r"); 
    //initialize .khs file pointer for reading
    FILE *KHSP = init_filepointer(khsfilename, "r"); 
    
    char readVal[STRLEN] = "";
    key2val(KVP, KHSP, searchTerm, readVal);

    if(strcmp(readVal, "") == 0){
        printf("NOT FOUND\n"); 
    }else{
       printf("%s\n", readVal); 
    }

    fclose(KVP); 
    fclose(KHSP); 
    
}

FILE * init_filepointer(char *filename, char* mode){
    FILE *FP; 
    if((FP = fopen(filename, mode)) == NULL){
        printf("%s could not be opened\n", filename);
        exit(1); 
    }
    return FP; 
}

void key2val( FILE *KVP, FILE *KHSP, char *searchTerm, char *readVal){
    int readIndex = 0; 
    char readKey[STRLEN] = ""; 
    int cap = get_capacity(KHSP);
    int hashval = hashfn(searchTerm, cap);
    //search for key's value 
    int j = 0; 
    read_index(KHSP, hashval, &readIndex);
    while(j < cap && readIndex != -1){ //how to check if key null?
        read_key(KVP, readIndex, readKey);
        if(strcmp(readKey, searchTerm) == 0){
           read_val(KVP, readIndex, readVal); 
           return; 
        }
        hashval++; j++; 
        if(hashval == cap){
            hashval = 0; 
        } 
        read_index(KHSP, hashval, &readIndex); 
    }
}

