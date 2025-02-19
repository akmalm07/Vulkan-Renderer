#pragma once
#include "config.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <type_traits>

namespace tools
{
	template <typename T>
	class MemoryPool
	{
	public:

		MemoryPool(size_t size);

		template <typename... Args>
		T* allocate(Args&&... args);

		void deallocate(void* ptr);

		void deallocate_all();

		void reset();

		bool contains(void* ptr) const;

		size_t available_memory() const;

		size_t get_offset() const;

		bool is_full() const;

		void resize(size_t newSize);

		~MemoryPool();

	private:

		std::vector<T> _pool;
		size_t _offset;
		size_t _size;
		std::unordered_map<void*, std::function<void(void*)>> _destructors;

		static size_t align(size_t offset, size_t alignment);
	};



	template <typename T>
	template <typename... Args>
	T* MemoryPool::allocate(Args&&... args)
	{
		size_t alignment = alignof(T);
		_offset = align(_offset, alignment);

		if (_offset + sizeof(T) > _size)
		{
			throw std::bad_alloc();
		}

		void* ptr = _pool.data() + _offset;
		_offset += sizeof(T);

		T* obj = new (ptr) T(std::forward<Args>(args)...);

		_destructors[ptr] = [](void* objPtr)
			{
				static_cast<T*>(objPtr)->~T();
			};

		return obj;
	}



	template<typename T>
	template<typename ...Args>
	inline T* MemoryPool<T>::allocate(Args && ...args)
	{
		size_t alignment = alignof(T);
		_offset = align(_offset, alignment);

		if (_offset + sizeof(T) > _size)
		{
			throw std::bad_alloc();
		}

		void* ptr = _pool.data() + _offset;
		_offset += sizeof(T);


		return new (ptr) T(std::forward<Args>(args)...);
	}

}