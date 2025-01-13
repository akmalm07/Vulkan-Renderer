#pragma once

#include <array>
#include <type_traits>

namespace std {

	template <class TY, class KY, size_t SI>
	class ordered_array
	{
	public:

		ordered_array()
		{
			arr.fill({}); 
			currentIndex = 0;
		}

		ordered_array(int inc)
		{
			
			for (; inc < SI; inc++)
			{
				arr[i] = { TY{}, static_cast<KY>(inc) }; 
				currentIndex++;
			}
		}
		
		ordered_array(ordered_array&& other) noexcept
			: arr(std::move(other.arr)), 
			currentIndex(other.currentIndex)  
		{
			other.currentIndex = 0; 
		}
		
		ordered_array& operator=(ordered_array&& other) noexcept
		{
			if (this != other)
			{
				arr = std::move(other.arr);
				currentIndex = other.currentIndex;
			}
			return *this;
		}



		bool is_full()
		{
			return (currentIndex == SI - 1);
		}


		TY find(const KY& key) const
		{
			for (const auto& [ky, val] : arr)
			{
				if (ky == key)
				{
					return val;
				}
			}
			throw std::runtime_error("Key not found!");
		}

		void erase(const KY& key)
		{
			for (size_t i = 0; i < currentIndex; ++i)
			{
				if (arr[i].first == key)
				{
					for (size_t j = i; j < currentIndex - 1; ++j)
					{
						arr[j] = arr[j + 1];
					}
					currentIndex--;
					return;
				}
			}
			throw std::runtime_error("Key not found");
		}

		void clear()
		{
			arr.fill({});
			currentIndex = 0;
		}

		size_t size() const { 
			return currentIndex; 
		}


		constexpr size_t capacity() const 
		{ 
			return SI; 
		}

		size_t size() const 
		{ 
			return currentIndex; 
		}
	
		constexpr size_t capacity() const 
		{ 
			return SI;
		}

		bool contains(const KY& key) const
		{
			for (const auto& [ky, val] : arr)
			{
				if (ky == key) 
				{
					return true;
				}
			}
			return false;
		}

		const TY& at(const KY& key) const
		{
			for (std::size_t i = 0; i < currentIndex; ++i)
			{
				if (arr[i].first == key)
				{
					return arr[i].second; 
				}
			}
			throw std::out_of_range("Key not found in ordered_array!");
		}




		pair<KY, TY>& operator[](KY&& key)
		{

			for (std::size_t i = 0; i < currentIndex; i++)
			{
				if (arr[i].first == key)
				{
					return arr[i]; 
				}
			}

			if (currentIndex < SI)
			{
				arr[currentIndex] = { std::forward<KY>(key), TY{} };
				return arr[currentIndex++]; 
			}
			else
			{
				throw std::out_of_range("Exceeded maximum capacity");
			}
		}

		TY& operator[](KY&& key)
		{
			for (std::size_t i = 0; i < currentIndex; ++i)
			{
				if (arr[i].first == key)
				{
					return arr[i].second; 
				}
			}

			throw std::runtime_error("This key does not exist in the array");
		}

		TY find(KY&& key)
		{
				
		}

		auto begin() { 
			return arr.begin(); 
		}

		auto end() 
		{ 
			return arr.begin() + currentIndex; 
		}

		auto begin() const 
		{
			return arr.begin(); 
		}

		auto end() const 
		{ 
			return arr.begin() + currentIndex; 
		}

		~ordered_array()
		{
			currentIndex = 0;
		}

	private:
		std::array<std::pair<KY, TY>, SI> arr;  
		size_t currentIndex; 

	private:

		std::string convert_key(const char* key)
		{
			return std::string(key); 
		}
	};

}

