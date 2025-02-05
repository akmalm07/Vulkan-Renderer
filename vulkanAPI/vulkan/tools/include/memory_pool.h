#pragma once

namespace vkUtil
{


	class MemPool
	{
	public:
		MemPool();

		MemPool(size_t size);

		void* allocate(size_t size);



		bool isFull() const;

		~MemPool();

	private:
		void* _pool;
		void* _current;
		size_t _size;
		size_t _sizeLeft;

	};

}