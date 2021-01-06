#include "array.h"
#include <stdio.h>

int main(){
    printf("bit\n"); 
    struct Performance *pp = newPerformance(); 
    printf("bit\n"); 
    struct Array *baby = newArray(pp, sizeof(int), 20); 
    printf("bit\n"); 
    int i=0; 
    for( i = 0; i < 8; i++){
        int day = 14 + i; 
        appendItem(pp, baby, &day); 
    }
    printf("bit\n"); 
    int numma = 100; 
    insertItem(pp, baby, 4, &numma); 
    printf("bit\n"); 
    int nu = 1111; 
    prependItem(pp, baby, &nu);

    deleteItem(pp, baby, 3); 

    for(i = 0; i < 10; i++){
        int destiny = 0; 
        readItem(pp, baby, i, &destiny); 
        printf("%d\n", destiny); 
    }
    

    printf("%d width\n", baby->width);

    return 0; 
}