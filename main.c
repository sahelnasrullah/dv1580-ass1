
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "main.h"

void* memory_pool = NULL;

size_t memory_size = 0;  // Positive integer
size_t memory_used = 0;  

void mem_init(size_t size) {
/* Initializes the memory manager with a specified size of memory pool. 
The memory pool could be any data structure, for instance, a large array or a similar contuguous block of memory.
(You do not have to interact directly with the hardware or the operating system’s memory management functions).*/
    
    
    memory_pool = malloc(size);
    memory_size = size;

    if (memory_pool == NULL) {
        printf("Failed to allocate");

    }

    memset(memory_pool, 0, size);
    memory_used = 0;

}

void* mem_alloc(size_t size) {
/*Allocates a block of memory of the specified size. 
Find a suitable block in the pool, mark it as allocated, and return the pointer to the start of the allocated block.*/

if (size + memory_used > memory_size){
    printf("Memory Full");
    return NULL;
}

void* ptr = (void*) memory_pool;
memory_used += size;
return ptr;

}

// Create blocks to see which are in use and which are not
// Freeing multiple blocks and being to use 3 previous blocks as one new block and the opposite using 1 big previous block to 3 small ones.

void mem_free(void* block) {
/*Frees the specified block of memory. 
For allocation and deallocation, you need a way to track which parts of the memory pool are free and which are allocated.*/  
    free(block);  
}

void* mem_resize(void* block, size_t size) {
/*Changes the size of the memory block, possibly moving it.*/
   void * ptr = realloc(block,size);
   return ptr;
}

void mem_deinit() {
/*Frees up the memory pool that was initially allocated by the mem_init function, 
ensuring that all allocated memory is returned to the system.*/
free(memory_pool);
memory_pool = NULL;
memory_size = 0;
memory_used = 0;
}

int main(void) {
    mem_init(1000);

    void* ptr1 = mem_alloc(100);
    void* ptr2 = mem_alloc(200);

    printf("Allocated memory: %p and %p\n", ptr1, ptr2);
    void* ptr3 = mem_alloc(800);  
    printf("%p",ptr3);

    mem_deinit();

    return 0;
}
