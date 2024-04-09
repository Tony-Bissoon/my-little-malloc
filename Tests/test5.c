#include <stdio.h>
#include "mymalloc.h"

/*

Single Allocation and Deallocation:
Ensure the allocator can handle a single, small allocation and deallocation, 
serving as the most basic check for its operational status.

*/

int test5() {
    // Step 1: Allocate a small amount of memory
    char *testPtr = (char *)malloc(16); // Request 16 bytes

    // Step 2: Check allocation success
    if (testPtr == NULL) {
        fprintf(stderr, "Test 5: Failed to allocate memory\n");
        return 0; // Indicate failure
    }

    // Optional: Use allocated memory
    for (int i = 0; i < 16; ++i) {
        testPtr[i] = 'A'; // Simple usage example
    }
    printf("Test 5: Memory allocation and usage successful\n");

    // Step 3: Free allocated memory
    free(testPtr);
    printf("Test 5: Memory deallocation successful\n");

    return 1; // Indicate success
}

int main(void) {
    if (test5()) {
        printf("Test 5 PASSED\n");
    } else {
        fprintf(stderr, "Test 5 FAILED\n");
    }

    return 0;
}
