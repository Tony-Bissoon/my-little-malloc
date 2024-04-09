#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mymalloc.h"

// Function to measure time in microseconds
long long current_timestamp() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000000LL + tp.tv_usec;
}

// Test Case 1: use malloc() and immediately free() a 1-byte object, 120 times.
static int testCase_1(){
    for (int i = 0; i < 120; i++) {
        void *pointer = malloc(1);
        if (pointer == NULL) {
            return -1;
        }
        free(pointer);
    }
    return 0;
}

/* Test case 2: Use malloc() to get 120 1-byte objects, 
   storing the pointers in an array, then use free() to deallocate the chunks.
*/
static int testCase_2(){
    char *ptr[120] = { NULL };

    for (int i = 0; i < 120; i++) {
        ptr[i] = malloc(1);
        if (ptr[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(ptr[i]);
            }
            return -1;
        }
    }

    for (int i = 0; i < 120; i++) {
        free(ptr[i]);
    }
    return 0;
}

/*
Test Case 3: Create an array of 120 pointers. 
Repeatedly make a random choice between allocating a 1-byte object and adding the pointer to the array and 
deallocating a previously allocated object (if any), until you have allocated 120 times. 
Deallocate any remaining objects.
*/ 
static int testCase_3(){
    int i, dealo = 0, alo = 0;
    char *pointer[120];
    int malo = 120, fre = 0; // malloc and free 

    for (i = 0; i < 240; i++) {
        // decide to malloc or free
        const int v = rand() % (malo + fre);

        if (v < fre) {
            free(pointer[dealo]);
            dealo++;
            fre--;
        } else {
            fre++;
            malo--;
            pointer[alo++] = malloc(1);
            if (pointer == NULL) {
                return -1;
            }
        }
    }
    return 0;
}
/* Test Case 4: This code allocates a 4096 byte block of memory using malloc, 
checks if the pointer is NULL, and returns -1 if so, indicating allocation failure.
*/
static int testCase4(){
    void *pointer1 = malloc(4096);
  if (pointer1 == NULL)
  {
    return -1;
  }

  void *pointer2 = malloc(1);
  if (pointer2 != NULL)
  {
    return -1;
  }

  free(pointer1);

  return 0;
}

static int testCase5() {
    // Allocate memory with size 0, which might behave differently on different systems
    void *pointer = malloc(0);
    
    // Check if memory allocation was successful
    if (pointer != NULL) {
        return -1; // Return -1 if allocation was successful (shouldn't be)
    }

    // Attempt to free a NULL pointer (should not cause any issues)
    free(NULL);

    // Allocate memory with size 20 bytes
    pointer = malloc(20);
    
    // Check if memory allocation was successful
    if (pointer == NULL) {
        return -1; // Return -1 if allocation failed
    }

    // Attempt to free a portion of the allocated memory (10 bytes after the start)
    free((char *)pointer + 10); // Casting to char pointer for correct byte arithmetic
    
    // Free the entire block of memory allocated earlier
    free(pointer);

    return 0; // Return 0 indicating successful execution
}
   



int main(void) {
    const int TOTAL_REPS = 50;
    long long total_time[5] = {0}; // Array to store total time for each test case

    srand(getpid());

    for (int i = 0; i < TOTAL_REPS; i++) {
        // Measure time for each test case
        long long start_time, end_time;

        start_time = current_timestamp();
        if (testCase_1() < 0) {
            fprintf(stderr, "Test case 1 FAILED\n");
            return 1;
        }
        end_time = current_timestamp();
        total_time[0] += end_time - start_time;

        start_time = current_timestamp();
        if (testCase_2() < 0) {
            fprintf(stderr, "Test case 2 FAILED\n");
            return 1;
        }
        end_time = current_timestamp();
        total_time[1] += end_time - start_time;

        start_time = current_timestamp();
        if (testCase_3() < 0) {
            fprintf(stderr, "Test case 3 FAILED\n");
            return 1;
        }
        end_time = current_timestamp();
        total_time[2] += end_time - start_time;

        start_time = current_timestamp();
        if (testCase4() < 0) {
            fprintf(stderr, "Test case 4 FAILED\n");
            return 1;
        }
        end_time = current_timestamp();
        total_time[3] += end_time - start_time;

        start_time = current_timestamp();
        if (testCase5() < 0) {
            fprintf(stderr, "Test case 5 FAILED\n");
            return 1;
        }
        end_time = current_timestamp();
        total_time[4] += end_time - start_time;
    
    }

    // Calculate average time for each test case
    for (int i = 0; i < 5; i++) {
        total_time[i] /= TOTAL_REPS;
    }

    // Print average time for each test case
    printf("Overall time to execute test 1 %.2f\n", (double)total_time[0]);
    printf("Overall time to execute test 2 %.2f\n", (double)total_time[1]);
    printf("Overall time to execute test 3 %.2f\n", (double)total_time[2]);
    printf("Overall time to execute test 4 %.2f\n", (double)total_time[3]);
    printf("Overall time to execute test 5 %.2f\n", (double)total_time[4]);
    return 0;
}
