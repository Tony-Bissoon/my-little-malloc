#include <stdio.h>
#include "mymalloc.h"

/*
Sequential Allocations and Immediate Deallocations:
To verify the allocator can handle multiple sequential allocations 
and immediate deallocations without encountering errors 
such as out-of-memory conditions for small, predictable requests.

*/
#define ALLOC_COUNT 10  // Number of allocations to perform
#define ALLOC_SIZE 32   // Size of each allocation in bytes

int testCase4() {
    void* ptrs[ALLOC_COUNT];
    int success = 1;

    // Perform a series of allocations
    for (int i = 0; i < ALLOC_COUNT; ++i) {
        ptrs[i] = malloc(ALLOC_SIZE);
        if (ptrs[i] == NULL) {
            fprintf(stderr, "Allocation failed at iteration %d\n", i);
            success = 0;
            break;  // Exit if any allocation fails
        }
    }

    // Immediately deallocate everything
    for (int i = 0; i < ALLOC_COUNT; ++i) {
        if (ptrs[i] != NULL) {
            free(ptrs[i]);
        }
    }

    return success;  // Returns 1 on success, 0 on failure
}

int main(void) {
    if (testCase4()) {
        printf("Test case 4 PASSED\n");
    } else {
        fprintf(stderr, "Test case 4 FAILED\n");
    }

    return 0;
}
