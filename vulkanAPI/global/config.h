#pragma once

#include <vulkan\vulkan.hpp>

#include <GLFW\glfw3.h>																				


#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>



//USER DEFITIONS
using pos = std::nullptr_t;

using col = std::nullptr_t;

using norm = std::nullptr_t;

using tex = std::nullptr_t;






#define UINT32(x) static_cast<uint32_t>(x)

#define SIZET(x) static_cast<size_t>(x)

#define ASSERT(cond, msg) if (!(cond)) { std::cerr << msg << std::endl; } 

#define INDEX_TYPE uint16_t 

using Index = INDEX_TYPE; 


namespace vkType
{
	template <class T>
	concept GLMVec = std::same_as<T, glm::vec2> || std::same_as<T, glm::vec3> ||
		std::same_as<T, glm::vec4> || std::same_as<T, std::nullptr_t>;


	template<class T>
	concept IndexType = std::is_same_v<T, uint32_t> || std::is_same_v<T, uint16_t>;


	template <GLMVec POS, GLMVec COL, GLMVec NORM, GLMVec TEX>
	struct Vertex
	{
		using Position = POS;
		using Color = COL;
		using Normal = NORM;
		using Texture = TEX;
	};



	template <class T>
	concept Struct = std::is_class_v<T> && requires { typename T::Position; typename T::Color; typename T::Normal; typename T::Texture; };



	template<IndexType T>
	vk::IndexType convert_type_to_vk_index_enum()
	{
		if constexpr (std::is_same_v<T, uint32_t>)
		{
			return vk::IndexType::eUint32;
		}
		else if constexpr (std::is_same_v<T, uint16_t>)
		{
			return vk::IndexType::eUint16;
		}
		else
		{
			std::cout << "Error: Unknown type is inputted for Convert Type To Enum!\n";
			return vk::IndexType::eNoneKHR;
		}
	}


	using Index = INDEX_TYPE;

	template<class T>
	concept BufferType = std::same_as<T, float> || std::same_as<T, Index>;

} // namespace vkType