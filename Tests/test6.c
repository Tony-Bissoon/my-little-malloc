#include <stdio.h>
#include "mymalloc.h"

/*
Allocates memory using malloc, frees it, and then attempts to free it again, resulting in"double free or corruption"
*/
int main(){
    void* p = malloc(1);
    free(p);
    free(p);
 
}