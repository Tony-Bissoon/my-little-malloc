# my-little-malloc
### CS214 Systems Programming Project 1: My little malloc()

MEMGRIND- Test Cases 4 and 5 
Test Case 4: This code allocates a 4096 byte block of memory using malloc, 
checks if the pointer is NULL, and returns -1 if so, indicating allocation failure.

Test Case 5: The goal is to test edge cases of malloc() and free() usage and verify expected behavior. Invalid usage like freeing partial memory is checked to see if it causes crashes or issues.
The return values indicate success or failure of different test scenarios and is focused on testing malloc/free correctness in different conditions.

Additional Test Programs(Test 1-8):
1. test1.c : Called malloc() function with an argument of 0 and then returns 0. 
    Result: malloc(0) doesn't allocate any memory.

2. test2.c : Allocates memory for 5 integers using mymalloc, initializes each integer to its index in the loop, and prints out the address and value of each allocated int.

3. test3.c : Calling free() with a NULL pointer results in an error message and does not actually free anything.

4. test4.c : Sequential Allocations and Immediate Deallocations: To verify the allocator can handle multiple sequential allocations and immediate deallocations without encountering errors such as out-of-memory conditions for small, predictable requests.

5. test5.c : Single Allocation and Deallocation: Ensure the allocator can handle a single, small allocation and deallocation, serving as the most basic check for its operational status.

6. test6.c : Allocates memory using malloc, frees it, and then attempts to free it again, resulting in"double free or corruption"

7. test7.c : Allocates memory of increasing size using malloc() in a loop, prints the allocated size, and then frees the memory before allocating again. Finds the maximum size that can be allocated as 4096 bytes based on the system's malloc implementation and memory availability

8. test8.c : Dynamically allocates memory of increasing sizes using malloc() in a loop and prints the allocated size at each iteration until allocation fails to demonstrate dynamic memory usage.



