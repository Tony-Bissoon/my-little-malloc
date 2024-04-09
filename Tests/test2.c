#include <stdio.h>
#include "mymalloc.h"

/*
Allocates memory for 5 integers using mymalloc, 
initializes each integer to its index in the loop, 
and prints out the address and value of each allocated int.

*/

int main(){
    int i;
    for(i = 0; i < 5; i++){
        int* p = malloc(sizeof(int));
        *p = i;
        printf("address: %p, value: %d\n",p, *p);
    }

}