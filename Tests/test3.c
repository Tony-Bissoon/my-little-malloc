#include <stdio.h>
#include "mymalloc.h"

/*
Calling free() with a NULL pointer results in an error message and does not actually free anything.
*/
int main(){
    free(NULL);
    return 0;
}