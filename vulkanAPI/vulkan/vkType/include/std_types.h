#pragma once

#include "pch.h"



namespace vkType {

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


	//template <GLMVec POS, GLMVec COL, GLMVec NORM, GLMVec TEX>
	//struct VertStd
	//{

	//};



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

}