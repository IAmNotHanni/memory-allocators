#pragma once

#include <spdlog/spdlog.h>

#include <cassert>
#include <memory>
#include <mutex>

namespace memory_allocators::pool_allocator {

/// @brief A chunk of memory for pool allocators.
template <typename T>
union PoolChunk {
    T value;
    PoolChunk<T> *next;
};

/// @brief A pool allocator.
template <typename T>
class PoolAllocator {
private:
    static constexpr std::size_t POOL_ALLOCATOR_DEFAULT_SIZE{1024};
    PoolChunk<T> *m_data{nullptr};
    PoolChunk<T> *m_head{nullptr};
    std::atomic<std::uint32_t> m_open_allocations{0};
    std::mutex m_mutex;

public:
    explicit PoolAllocator(const std::size_t pool_size = POOL_ALLOCATOR_DEFAULT_SIZE) {
        assert(pool_size > 0);

        m_data = new PoolChunk<T>[pool_size]; // NOLINT

        m_head = m_data;

        for (std::size_t i = 0; i < pool_size - 1; i++) {
            m_data[i].next = std::addressof(m_data[i + 1]); // NOLINT
        }

        m_data[pool_size - 1].next = nullptr; // NOLINT
    }

    PoolAllocator(const PoolAllocator &) = delete;
    PoolAllocator(PoolAllocator &&) = delete;

    PoolAllocator &operator=(const PoolAllocator &) = delete;
    PoolAllocator &operator=(PoolAllocator &&) = delete;

    ~PoolAllocator() noexcept {
        std::unique_lock lock(m_mutex);

        delete[] m_data;
        m_data = nullptr;
        m_head = nullptr;

        // Make sure to free all the memory we know about before checking if we didn't free everything.
        if (m_open_allocations > 0) {
            spdlog::critical("Pool allocator has lost memory chunks!");
        }
    }

    /// @brief Allocate a new object.
    template <typename... arguments>
    [[nodiscard]] T *allocate(arguments &&...args) {
        if (m_head == nullptr) {
            throw std::runtime_error("Error: Pool allocator of memory!");
        }

        std::unique_lock lock(m_mutex);
        PoolChunk<T> *chunk = m_head;
        m_head = m_head->next;

        T *allocated_chunk{nullptr}; // NOLINT

        try {
            allocated_chunk = new (std::addressof(chunk->value)) T(std::forward<arguments>(args)...); // NOLINT
        } catch (const std::exception &result) {
            spdlog::critical("Could not allocate object!");
            // Continue throwing the exception because allocation of the object failed!
            throw;
        }
        m_open_allocations++;
        return allocated_chunk;
    }

    /// @brief Deallocate an object and give it back to the object pool.
    void destroy(T *data) {
        assert(data);
        // TODO: What if data is not part of m_data?

        std::unique_lock lock(m_mutex);

        // Call the destructor of the object.
        // std::destroy(data);
        data->~T();

        // Take back the memory block to the memory pool.
        PoolChunk<T> *chunk = reinterpret_cast<PoolChunk<T> *>(data); // NOLINT

        chunk->next = m_head;
        m_head = chunk;
        m_open_allocations--;
    }
};
} // namespace memory_allocators::pool_allocator
