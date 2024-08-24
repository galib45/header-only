# Header-Only Libraries
This repository hosts various header-only libraries created by the owner.

## Current Libraries
- `arena.h` provides a simple memory arena allocation system. It includes:
  - Platform-Specific Allocation: Uses VirtualAlloc on Windows and malloc on other platforms.
  - Region-Based Allocation: Manages memory in chunks (regions) to reduce frequent allocations and deallocations.
  - API Functions:
    - arena_alloc(Arena *a, size_t bytes): Allocates a block of memory from the arena.
    - arena_free(Arena *a): Frees all memory allocated by the arena.
  - Key Components:
    - Region: Represents a block of memory within the arena.
    - Arena: Manages multiple Region objects for efficient memory allocation.
  - Usage Example:
    ```c
    #include "arena.h"
    
    int main() {
        Arena arena = {0};
        void *mem = arena_alloc(&arena, 128);
        // Use the allocated memory
        arena_free(&arena);
        return 0;
    }
    ```

## License
This repository is licensed under the Unlicense, which means you can freely use, modify, and distribute the code without any restrictions.

## Contributing
Contributions are welcome! Feel free to add new header-only libraries or enhance existing ones. Ensure that all code adheres to the Unlicense.
