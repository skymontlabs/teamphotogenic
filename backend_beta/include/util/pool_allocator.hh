#include <cstdlib>
#include <vector>
#include <iostream>

using std::vector;

class PoolAllocator
{
    struct Block
    {
        Block* next;
    };

    struct Pool
    {
        size_t blockSize;
        vector<uint8_t*> pages;
        Block* freeListHead;
        size_t blocksPerPage;

        Pool(size_t size):
        blockSize(size),
        freeListHead(nullptr)
        {
            // Calculate how many blocks per page
            blocksPerPage = 4096 / blockSize;
            if (4096 % blockSize != 0) {
                blocksPerPage--;
            }
        }

        ~Pool()
        {
            for (unsigned char* page : pages)
                free(page);
        }

        void allocatePage()
        {
            unsigned char* newPage = static_cast<unsigned char*>(malloc(4096));
            pages.push_back(newPage);

            // Link the new blocks
            for (size_t i = 0; i < blocksPerPage; ++i) {
                Block* block = reinterpret_cast<Block*>(newPage + i * blockSize);
                block->next = freeListHead;
                freeListHead = block;
            }
        }

        void* allocate()
        {
            if (!freeListHead)
                allocatePage();

            // Allocate a block from the pool
            Block* block = freeListHead;
            freeListHead = freeListHead->next;
            return block;
        }

        void deallocate(void* ptr)
        {
            // Add the block back to the pool
            Block* block = static_cast<Block*>(ptr);
            block->next = freeListHead;
            freeListHead = block;
        }

        bool isFromPool(void* ptr) const
        {
            for (unsigned char* page : pages) {
                if (ptr >= page && ptr < page + 4096) {
                    return true;
                }
            }
            return false;
        }
    };

    vector<Pool> pools;

public:
    PoolAllocator(size_t baseBlockSize)
    {
        for (size_t size = baseBlockSize; size <= (baseBlockSize << 6); size <<= 1) {
            pools.emplace_back(size);
        }
    }

    void* allocate(size_t size)
    {
        for (auto& pool : pools) {
            if (size <= pool.blockSize) {
                return pool.allocate();
            }
        }
        // Fallback to malloc if no pool fits the size
        return nullptr;
    }

    void deallocate(void* ptr, size_t size)
    {
        for (auto& pool : pools) {
            if (size == pool.blockSize && pool.isFromPool(ptr)) {
                pool.deallocate(ptr);
                return;
            }
        }
        // Fallback to free if no pool owns the pointer
        return;
    }
};

/*
// Example usage:
int main() {
    PoolAllocator allocator(64); // Create a pool allocator with base block size of 64 bytes

    void* block1 = allocator.allocate(64); // Allocates from 64-byte pool
    void* block2 = allocator.allocate(128); // Allocates from 128-byte pool

    allocator.deallocate(block1, 64); // Deallocates block from 64-byte pool
    allocator.deallocate(block2, 128); // Deallocates block from 128-byte pool

    return 0;
}
*/
