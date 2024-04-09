#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.h"

#define SIZE 4096
#define META_SIZE sizeof(struct metaData)

struct metaData {
    unsigned char isUsed;
    unsigned short blocksize;
};

static char memory[SIZE + 2 * META_SIZE]; // Extra space for start and end meta

void memoryInitialize() {
    static int isInitialized = 0;
    if (!isInitialized) {
        isInitialized = 1;
        struct metaData *startMeta = (struct metaData *)memory;
        startMeta->isUsed = 0;
        startMeta->blocksize = SIZE;

        struct metaData *endMeta = (struct metaData *)(memory + META_SIZE + SIZE);
        endMeta->isUsed = 1; // Mark as used to stop the search
        endMeta->blocksize = 0; // Sentinel block
    }
}

static char *findFit(const size_t size) {
    char *iter = memory;
    while (1) {
        struct metaData *meta = (struct metaData *)iter;
        if (!meta->isUsed && meta->blocksize >= size) {
            return iter;
        }
        if (meta->blocksize == 0) { // Reached sentinel
            break;
        }
        iter += META_SIZE + meta->blocksize;
    }
    return NULL;
}

void *mymalloc(size_t size, char *file, int line) {
    if (size <= 0 || size > SIZE) {
        fprintf(stderr, "%s:%d: malloc: Invalid size\n", file, line);
        return NULL;
    }

    memoryInitialize(); // Ensure memory is initialized

    char *fit = findFit(size);
    if (!fit) {
        fprintf(stderr, "%s:%d: malloc: Out of memory\n", file, line);
        return NULL;
    }

    struct metaData *fitMeta = (struct metaData *)fit;
    size_t remaining = fitMeta->blocksize - size;
    if (remaining > META_SIZE + 8) { // Check if there's enough space to split
        struct metaData *newMeta = (struct metaData *)(fit + META_SIZE + size);
        newMeta->isUsed = 0;
        newMeta->blocksize = remaining - META_SIZE;

        fitMeta->blocksize = size;
    }

    fitMeta->isUsed = 1;
    return (void *)(fit + META_SIZE);
}

static void mergeFreeBlocks() {
    char *iter = memory;
    while (1) {
        struct metaData *current = (struct metaData *)iter;
        if (current->blocksize == 0) { // Reached sentinel
            break;
        }
        char *nextBlock = iter + META_SIZE + current->blocksize;
        struct metaData *next = (struct metaData *)nextBlock;

        if (!current->isUsed && next->blocksize != 0 && !next->isUsed) {
            // Merge current and next
            current->blocksize += META_SIZE + next->blocksize;
        } else {
            iter = nextBlock;
        }
    }
}

void myfree(void *ptr, char *file, int line) {
    if (!ptr) {
        fprintf(stderr, "%s:%d: free: Can't free NULL\n", file, line);
        return;
    }

    char *block = (char *)ptr - META_SIZE;
    struct metaData *meta = (struct metaData *)block;
    if (meta->isUsed) {
        meta->isUsed = 0;
        mergeFreeBlocks();
    } else {
        fprintf(stderr, "%s:%d: free: Double free or corruption\n", file, line);
    }
}

