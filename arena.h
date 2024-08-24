#ifndef ARENA_H
#define ARENA_H
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
    #include <windows.h>
    #define ALLOC(size) VirtualAlloc(NULL, (size), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)
    #define FREE(ptr) VirtualFree((ptr), 0, MEM_RELEASE)
#else
    #include <stdlib.h>
    #define ALLOC(size) malloc((size))
    #define FREE(ptr) free((ptr)) 
#endif

#define REGION_DEFAULT_CAPACITY 8192

typedef struct Region Region;
typedef struct Arena Arena;

struct Region {
    Region *next;
    size_t count;
    size_t capacity;
    uintptr_t data[];
};

struct Arena {
    Region *begin, *end;
};

Region *new_region(size_t capacity) {
    size_t size = sizeof(Region) + sizeof(uintptr_t)*capacity;
    Region *r = ALLOC(size);
    r->next = NULL;
    r->count = 0;
    r->capacity = capacity;
    return r;
}

void *arena_alloc(Arena *a, size_t bytes) {
    // alignment
    size_t size = (bytes + sizeof(uintptr_t) - 1)/sizeof(uintptr_t);
    size_t capacity = size > REGION_DEFAULT_CAPACITY ? size : REGION_DEFAULT_CAPACITY;
    if (a->end == NULL || a->begin == NULL) {
        a->end = new_region(capacity);
        a->begin = a->end;
    }
    if (a->end->count + size > a->end->capacity && a->end->next == NULL) {
        a->end->next = new_region(capacity);
        a->end = a->end->next;
    }
    void *result = &a->end->data[a->end->count];
    a->end->count += size;
    return result;
}

void arena_free(Arena *a) {
    Region *r = a->begin, *tmp;
    while (r) {
        tmp = r; r = r->next;
        FREE(tmp);
    }
}
#endif // ARENA_H
