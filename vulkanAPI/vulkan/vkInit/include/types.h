#pragma once

#include <cstdint>

#include "predefines.h"
#include <glm\glm.hpp>

#include <type_traits>



namespace vkType 
{
	using Index = INDEX_TYPE; 
	using Vertex = VERTEX_TYPE;

	class Drawable
	{};

	struct PushConst
	{
		uint32_t _offset;
		uint32_t _size;
		vk::ShaderStageFlagBits _shader;

		PushConst(uint32_t size, uint32_t offset, vk::ShaderStageFlagBits _shader)
			: _size(size), _offset(offset), _shader(_shader) {}


	};

	struct NULLOBJ
	{
		NULLOBJ() = default;
	};


	template <typename T, size_t S = 0>
	struct ArrOrVec 
	{
		static constexpr bool value = false;
	};

	template <typename T>
	struct ArrOrVec<std::vector<T>, 0> 
	{
		static constexpr bool value = true;
	};

	template <typename T, size_t S>
	struct ArrOrVec<std::array<T, S>, S> 
	{
		static constexpr bool value = true;
	};


	template <class T>
	concept IsNull = std::is_same_v<T, NULLOBJ>;

	template <class T>
	concept IsDrawable = std::is_base_of_v<Drawable, T>;


	template <class T>
	concept IsPushConst = std::is_base_of_v<PushConst, T>;

	template <class T>
	concept IsClass = std::is_class_v<T>; 

	template <class T>
	concept Callible = std::is_invocable_v<T>;

	template<class T, size_t S = 0>
	concept IsArrOrVec = ArrOrVec<T, S>::value;

	template<class Func, class ... Args>
	concept BoolLambdaVardic = std::invocable<Func, Args...>&& std::convertible_to<std::invoke_result_t<Func, Args...>, bool>;


	template <typename T>
	concept Enum = std::is_enum_v<T>;

	template <class T>
	concept VertBuff = std::same_as<OncePerVertBuffer, T> || std::same_as<AllInOneVertBuffer, T>;

	template <class T>
	concept ValidObj = std::is_class_v<T> && std::is_base_of_v<Drawable, T>;

	template <class T>
	concept PushConstant = std::is_class_v<T> && std::is_base_of_v<PushConst, T>;


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

	template<class T>
	const T make_const(T&& t)
	{
		const T val = t;
		return val;
	}


	template <class T>
	concept Struct = std::is_class_v<T> && requires { typename T::Position; typename T::Color; typename T::Normal; typename T::Texture; };
	
	template <class T>
	decltype(auto) ref(T&& t)
	{
		if constexpr (std::is_lvalue_reference_v<T>) 
		{
			return t;
		}
		else 
		{
			return std::forward<T>(t);
		}
	}

	template <class T>
	decltype(auto) val(T&& t)
	{
		return std::decay_t<T>(std::forward<T>(t));
	}


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