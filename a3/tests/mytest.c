#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/**
 * Name: mytest.c
 * Author: Michelle Berry
 * Purpose: test A3 of CIS*2520 Data Structures assignment 3.
 *          tests push, readHead, pop, next, isEmpty, and freeList.
 * Last Updated: Oct 5th, 2020.
 **/

int main(){
    struct Node *head = NULL;
    struct Node **list_ptr;

    list_ptr = &head; 

    struct Performance *pp = newPerformance(); 
    printf("\ntest zero: push multiples of 10\n\n\n"); 
    int i;
    for(i = 10; i < 110; i+=10){
        push(pp, list_ptr, &i, sizeof(int));        //push so result: 100 90 80 70 60 50 40 30 20 10
    }

    printf("test one: read head\n");
    int readOne;
    readHead(pp, list_ptr, &readOne, sizeof(int));  //read head (100)
    printf("%d\n", readOne); 

    printf("\ntest two: pop head off \n\n\n");
    void *dest = malloc(sizeof(int)); 
    pop(pp, list_ptr, dest, sizeof(int));           //remove 100 (pop from head)
    free(dest); 

    printf("test three: read head\n");
    readHead(pp, list_ptr, &readOne, sizeof(int));  //read head (100)
    printf("%d\n", readOne); 
   
    printf("\ntest four: print list\n"); 
    struct Node *headB = head;
    while(headB != NULL){
        int *datah = (int *)headB->data;      
        printf("%d\n", *datah); 
        headB = headB->next; 
    }

    printf("\ntest four.5: append 666 to list\n"); 
    int nomber = 666; 
    appendItem(pp, &head, &nomber, sizeof(int)); 

    printf("\ntest four.6: insert 667 to index 5\n"); 
    nomber++;
    insertItem(pp, &head, 5, &nomber, sizeof(int)); 

    printf("\ntest four.7: prepend 668\n"); 
    nomber++;
    prependItem(pp, &head, &nomber, sizeof(int));

    printf("\ntest four.8: delete 20\n"); 
    deleteItem(pp, &head, 9);

    printf("\ntest five: print list using next\n");
    while(!isEmpty(pp, list_ptr)){ //while is not empty
        readHead(pp, list_ptr, &readOne, sizeof(int));  //read head 
        printf("%d\n", readOne); 

        list_ptr = next(pp,list_ptr); 
    }

    printf("\ntest six: read item at 5\n");
    readItem(pp, &head, 5, &readOne, sizeof(int));
    printf("%d\n", readOne);

    printf("\ntest seven: free memory. (run with valgrind to check).\n");
    list_ptr = &head; 
    freeList(pp, list_ptr); 
    free(pp); 

    return 0; 
}