#include <stdio.h>
#include "mymalloc.h"

/*
Allocates memory of increasing size using malloc() in a loop, 
prints the allocated size, and then frees the memory before allocating again.
Finds the maximum size that can be allocated as 4096 bytes based on the system's malloc implementation and memory availability
*/
int main(){
    void* p;
    int i;
    for(i = 1; (p = malloc(i)) != NULL; i++){
        printf("%d bytes allocated\n", i);
        free(p);
    }
}