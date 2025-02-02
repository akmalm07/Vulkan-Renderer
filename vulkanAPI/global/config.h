#pragma once

#include <vulkan\vulkan.hpp>

#include <GLFW\glfw3.h>																				

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <list>
#include <cstddef>
#include <iterator>


#define UINT32(x) static_cast<uint32_t>(x)

#define SIZET(x) static_cast<size_t>(x)

#define ASSERT(cond, msg) if (!(cond)) { std::cerr << msg << std::endl; } 

#define INDEX_TYPE uint16_t 

#define VERTEX_TYPE float 


using OncePerVertBuffer = vk::VertexInputAttributeDescription;
using AllInOneVertBuffer = std::vector<vk::VertexInputAttributeDescription>;




inline void CheckVkResult(vk::Result result)
{ 
	if (result != vk::Result::eSuccess) 
	{
		throw std::runtime_error("Vulkan Error: " + vk::to_string(result) + "\n");
	}
}

namespace UserInput
{
	//USER DEFITIONS
	using pos = glm::vec2;

	using col = glm::vec3;

	using norm = std::nullptr_t;

	using tex = std::nullptr_t;

	using AttributeDescription = AllInOneVertBuffer; 

	const char v_shader_path[] = "..\\shaders\\vertex.spv"; 
	const char f_shader_path[] = "..\\shaders\\fragment.spv"; 



} // namespace UserInput




#define DEBUG

#ifndef NDEBUG

#define VK_CHECK_RESULT(f) {																	\
		auto res = (f);																			\
		if (res != vk::Result::eSuccess) {														\
			std::cerr << "Fatal : VkResult is \"" << vk::to_string(res) << "\" in " << __FILE__	\
				<< " at line " << __LINE__ << std::endl;											\
			assert(res == vk::Result::eSuccess);													\
		}																						\
	}		\


#define DEBUG_ITERATOR(vec, statement) for (const auto& item : vec) { statement; }

#endif

namespace vkType
{
	using Index = INDEX_TYPE;   
	using Vertex = VERTEX_TYPE;   

	class Drawable
	{};

	struct PushConst
	{
		const uint32_t _offset; 
		const uint32_t _size;
		const vk::ShaderStageFlagBits _shader;

		PushConst( uint32_t size, uint32_t offset, vk::ShaderStageFlagBits _shader)
			: _size(size), _offset(offset), _shader(_shader) {}

	};

	struct NULLOBJ
	{
		NULLOBJ() = default;
	};


	template <class T>
	concept VertBuff = std::same_as<OncePerVertBuffer, T> || std::same_as<AllInOneVertBuffer, T>; 

	template <class T>
	concept ValidObj = std::is_class_v<T> &&  std::is_base_of_v<Drawable, T>; 

	template <class T>
	concept PushConstant = std::is_class_v<T> &&  std::is_base_of_v<PushConst, T>; 


	template <class T>
	concept GLM_TYPE = std::same_as<T, glm::vec2> || std::same_as<T, glm::vec3> ||
		std::same_as<T, glm::vec4>;

	template <class T>
	concept GLM_VEC_TYPE = GLM_TYPE<T> && requires(T t) { typename T::value_type; }; 

	template <class T>
	concept GLMVec = std::same_as<T, glm::vec2> || std::same_as<T, glm::vec3> ||
		std::same_as<T, glm::vec4> || std::same_as<T, std::nullptr_t>;

	template<class T>
	concept IndexType = std::is_same_v<T, uint32_t> || std::is_same_v<T, uint16_t>;
	

	template<class T>
	concept Arithmatic = std::is_arithmetic_v<T>; 


	//template <GLMVec POS, GLMVec COL, GLMVec NORM, GLMVec TEX>
	//struct Vertex
	//{
	//	using Position = POS;
	//	using Color = COL;
	//	using Normal = NORM;
	//	using Texture = TEX;
	//};



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