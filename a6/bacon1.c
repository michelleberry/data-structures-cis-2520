#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "hashfn.h"
#define MAX_CAST_SIZE 20

FILE * init_filepointer(char *filename, char* mode);
void key2val( FILE *KVP, FILE *KHSP, char *searchTerm, char *readVal);
void val2key( FILE *KVP, FILE *VHSP, char *searchTerm, char *readKey);

//1 degree of kevin bacon 
int main( int argc, char **argv){
    if(argc != 2){
        fprintf( stderr, "Usage: %s 'search term'\n", argv[0]);
        exit(0); 
    }

    char foundMovieTitle[STRLEN] = "";
    char movieKey[STRLEN] = ""; 
    char nameKey[STRLEN] = ""; 
    char tempVal[STRLEN] = ""; 
    char tempKey[STRLEN] = "";
    char kevinKey[STRLEN] = "";
    char actorKey[STRLEN] = "";
    char actorName[STRLEN] = ""; 
    strcpy(actorName, argv[1]);

    //open name basics kv and vhs
    FILE *NB_KV = init_filepointer("name.basics.kv", "r"); 
    FILE *NB_VHS = init_filepointer("name.basics.vhs", "r"); 

    val2key(NB_KV, NB_VHS, actorName, actorKey); //get actor name key 
    val2key(NB_KV, NB_VHS, "Kevin Bacon", kevinKey); // get kevin bacon key

    //close name basics; we no longer need it 
    fclose(NB_KV); 
    fclose(NB_VHS); 

    //open title principals
    FILE *TP_KV = init_filepointer("title.principals.kv", "r"); 
    FILE *TP_KHS = init_filepointer("title.principals.khs", "r");
    FILE *TP_VHS = init_filepointer("title.principals.vhs", "r"); 

    //open title basics we need dis
    FILE *TB_KV = init_filepointer("title.basics.kv", "r");
    FILE *TB_KHS = init_filepointer("title.basics.khs", "r"); 
    
    int nameIndex = 0;
    int index = 0;
    int cap = get_capacity(TP_VHS); 
    int hash1 = hashfn(actorKey, cap); //search for movies <the actor name> is in
    int hash2 = 0;  

    read_index(TP_VHS, hash1, &index);
    read_val(TP_KV, index, tempVal);
    int found = 0; 
    int found2 = 0;
    int loops = 0;  
    while (index != -1 && found == 0){
        //if we got a movie <they> are in,
        found2 = 0;  
        if((strcmp(tempVal, actorKey) == 0)){
            read_key(TP_KV, index, tempKey);    //get <their> movie key      
            hash2 = hashfn(tempKey, cap);   //find the index of that movie in the table
            read_index(TP_KHS, hash2, &nameIndex); 
            read_key(TP_KV, nameIndex, movieKey); 
            loops = 0; 
            while(found2 == 0){ //while the movie key is still the movie key from before 
                if(strcmp(movieKey, tempKey) == 0){
                    //get the nameKey
                    read_val(TP_KV, nameIndex, nameKey);
                    //if one of the actors in the movie is kevin
                    if(strcmp(nameKey, kevinKey) == 0){
                    key2val(TB_KV, TB_KHS, movieKey, foundMovieTitle); 
                    //print the movie 
                    printf("%s\n", foundMovieTitle);
                    //exit the loop
                    found = 1;                         //What if kevin isn't in the movie? 
                    found2 = 1; 
                    }
                } else if(loops == MAX_CAST_SIZE){
                    found = 1;                         //Exits the loop when it has searched as much as it should (prevent infinite loop in absence of kevin bacon)
                    found2 = 1;
                }
                loops++; 
                hash2++; 
                if(hash2 == cap || hash2 > cap){
                    hash2 = 0; 
                }
                read_index(TP_KHS, hash2, &nameIndex); 
                read_key(TP_KV, nameIndex, movieKey); 
            }
        }
            
        hash1++;
        if(hash1 == cap){
            hash1 = 0; 
        }
        read_index(TP_VHS, hash1, &index);
        read_val(TP_KV, index, tempVal);
    }

    fclose(TP_KV); 
    fclose(TP_KHS); 
    fclose(TP_VHS); 
    fclose(TB_KV); 
    fclose(TB_KHS); 

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