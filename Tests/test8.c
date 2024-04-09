#include <stdio.h>
#include "mymalloc.h"

int main(){
    void* p;
    int i;
    for(i = 1; (p = malloc(i)) != NULL; i++){
        printf("%d bytes allocated\n", i);
    }
}