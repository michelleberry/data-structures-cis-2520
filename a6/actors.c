#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "hashfn.h"

FILE * init_filepointer(char *filename, char* mode);
void key2val( FILE *KVP, FILE *KHSP, char *searchTerm, char *readVal);
int key2val_offset( FILE *KVP, FILE *KHSP, char *searchTerm, char *readVal, int offset);
void val2key( FILE *KVP, FILE *VHSP, char *searchTerm, char *readKey);

//takes a movie name as input (first cmd line arg) and lists all the actors in it 
//"you may assume the movie name exists and is correctly entered" ok but imma still check
int main( int argc, char **argv){
    if(argc != 2){
        fprintf( stderr, "Usage: %s 'movie title'\n", argv[0]); 
        exit(0); 
    }

    char movieName[STRLEN];
    strcpy(movieName, argv[1]);

    //open title basics kv and vhs
    FILE *TB_KV = init_filepointer("title.basics.kv", "r");
    FILE *TB_VHS = init_filepointer("title.basics.vhs", "r"); 
    //val2key the movie name 
    char movieNameKey[STRLEN] = ""; 
    val2key(TB_KV, TB_VHS, movieName, movieNameKey);
   
    //fclose title basics
    fclose(TB_KV); 
    fclose(TB_VHS); 

    //open title principals
    FILE *TP_KV = init_filepointer("title.principals.kv", "r"); 
    FILE *TP_KHS = init_filepointer("title.principals.khs", "r"); 
    //open name basics kv and khs
    FILE *NB_KV = init_filepointer("name.basics.kv", "r"); 
    FILE *NB_KHS = init_filepointer("name.basics.khs", "r"); 

    //w/ movie name key, key2val titleprincipals to get actor name KEYS ( multiple )
    //key2val each actor name
    char actorNameKey[STRLEN] = ""; char actorName[STRLEN] = ""; char prevActorName[STRLEN] = ""; int i = 0; 
    int found = key2val_offset(TP_KV, TP_KHS, movieNameKey, actorNameKey, i);

    //loop until actor keys cannot be found
    while( found == 1 ){
        key2val(NB_KV, NB_KHS, actorNameKey, actorName);
        if(strcmp(actorName, prevActorName) != 0){
           printf("%s\n", actorName); 
        }
        i++; 
        found = key2val_offset(TP_KV, TP_KHS, movieNameKey, actorNameKey, i);
        strcpy(prevActorName, actorName); 
    }

    fclose(TP_KV); 
    fclose(TP_KHS); 
    fclose(NB_KV); 
    fclose(NB_KHS); 
}

//initalize new file pointer, checking it has opened correctly
FILE * init_filepointer(char *filename, char* mode){
    FILE *FP; 
    if((FP = fopen(filename, mode)) == NULL){
        printf("%s could not be opened\n", filename);
        exit(1); 
    }
    return FP; 
}

//readVal contains value read using searchTerm/key.
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

//readVal contains value read using searchTerm/key.
int key2val_offset( FILE *KVP, FILE *KHSP, char *searchTerm, char *readVal, int offset){
    int readIndex = 0; 
    char readKey[STRLEN] = ""; 
    int cap = get_capacity(KHSP);
    int hashval = hashfn(searchTerm, cap) + offset;

    //search for key's value 
    int j = 0; 
    read_index(KHSP, hashval, &readIndex);
    while(j < (cap-offset-1) && readIndex != -1){
        //printf("khsp[%d] = kv[%d]\n", hashval, readIndex);
        read_key(KVP, readIndex, readKey);
        if(strcmp(readKey, searchTerm) == 0){
           read_val(KVP, readIndex, readVal); 
           return 1;  
        }
        hashval++; j++; 
        if(hashval == cap){
            hashval = 0; 
        } 
        read_index(KHSP, hashval, &readIndex);
    }
    return 0; 
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

