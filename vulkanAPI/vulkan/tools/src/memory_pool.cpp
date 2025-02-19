#include "pch.h"

#include "tools\include\memory_pool.h"


namespace tools
{


    MemoryPool::MemoryPool(size_t size)
        : _pool(size), _offset(0), _size(size)
    {
    }

    void MemoryPool::deallocate(void* ptr)
    {
        auto it = _destructors.find(ptr);
        if (it != _destructors.end())
        {
            it->second(ptr); 
            _destructors.erase(it);
        }
    }

    void MemoryPool::deallocate_all()
    {
        for (auto& [ptr, destructor] : _destructors)
        {
            destructor(ptr);
        }
        _destructors.clear();
    }

    void MemoryPool::reset()
    {
        deallocate_all();
        _offset = 0;
    }

    bool MemoryPool::contains(void* ptr) const
    {
        return (ptr >= _pool.data() && ptr < (_pool.data() + _size));
    }

    size_t MemoryPool::available_memory() const
    {
        return _size - _offset;
    }

    size_t MemoryPool::get_offset() const
    {
        return _offset;
    }

    bool MemoryPool::is_full() const
    {
        return _offset >= _size;
    }

    void MemoryPool::resize(size_t newSize)
    {
        if (newSize < _offset)
        {
            throw std::runtime_error("Cannot shrink memory pool below used memory size.");
        }
        _pool.resize(newSize);
        _size = newSize;
    }

    MemoryPool::~MemoryPool()
    {
        reset();
        deallocate_all();
    }

    size_t MemoryPool::align(size_t offset, size_t alignment)
    {
        return (offset + alignment - 1) & ~(alignment - 1);
    }

}