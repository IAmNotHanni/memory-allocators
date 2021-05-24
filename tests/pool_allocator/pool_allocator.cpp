#include <gtest/gtest.h>

#include "allocators/pool_allocator/pool_allocator.hpp"

namespace memory_allocators::pool_allocator {

TEST(PoolAllocator, Example1) {
    PoolAllocator<int> MyAllocator;

    int *number1 = MyAllocator.allocate(1337);
    int *number2 = MyAllocator.allocate(42);

    MyAllocator.destroy(number1);
    MyAllocator.destroy(number2);
}

} // namespace memory_allocators::pool_allocator
