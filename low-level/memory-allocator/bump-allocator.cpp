#include <cstddef>
#include <cstdlib>

// what learned
// char pointer is used for storing addresses of chars or array of chars
// char c = 'A';
// char str[6] = 'hello';
//
// void pointer is used to show the memory location of char pointer
// because char pointer does not null terminator like strings 
// so it will continue to read the memory
// until it encounters \0 - null terminator
// when we use void* it will not happen
//
// char* cptr = &c;
// or
// char* cptr = str;
// cout << (void*)cptr;
// cout << (void*)&c; to view the address of char
// void* - generic pointer
//

class BumpAllocator {
    char* start;
    size_t capacity;
    size_t offset;

public:
    BumpAllocator(size_t capacity) {
        start = (char*) std::malloc(capacity); // ask memory from os
        capacity = capacity;
        offset = 0;
    }

    void* alloc(size_t n) {
        // check if n does not exceed the initialized capacity
        if (offset + n > capacity) {
            return nullptr;
        }

        // allocate some memory
        void* ptr = start + offset;
        
        // update the allocated memory
        offset += n;

        return ptr;
    }

    // free everything
    void reset() {
        offset = 0;
    }

    // on destroy, give back memory to os
    ~BumpAllocator() {
        std::free(start);
    }

}

