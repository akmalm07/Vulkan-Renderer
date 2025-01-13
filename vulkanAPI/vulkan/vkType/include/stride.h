#pragma once
#include "pch.h"
#include "std_types.h"


namespace vkVert {

	enum class PosStride : uint8_t 
	{
		NONE = 0,
		STRIDE_2D,
		STRIDE_3D
	};

	enum class ColorStride : uint8_t
	{
		NONE = 0,
		RGB,
		RGBA
	};

	enum class NormalStride : uint8_t
	{
		NONE = 0,
		STRIDE_2D,
		STRIDE_3D
	};
	
	enum class TextureStride : uint8_t
	{
		NONE = 0,
		STRIDE_2D,
		STRIDE_3D
	};





	uint8_t enumerate_pos_stride(PosStride stride); 
	uint8_t enumerate_color_stride(ColorStride stride);
	uint8_t enumerate_tex_stride(TextureStride stride);
	uint8_t enumerate_normal_stride(NormalStride stride);

}


namespace vkType {

	using namespace vkVertex;


	template <GLMVec T>	
	PosStride enumify_pos_type()
	{
		if constexpr (std::is_same_v<T, glm::vec2>)   
		{
			return PosStride::STRIDE_2D;
		}
		else if constexpr (std::is_same_v<T, glm::vec3>) 
		{
			return PosStride::STRIDE_3D;
		}
		else if constexpr (std::is_same_v<T, std::nullptr_t>) 
		{
			return PosStride::NONE; 
		}
		else 
		{
			std::cout << "Error: an unknown type was entered for Position Stride!\n";
			return PosStride::NONE; 
		}
	}

	template <GLMVec T>	
	ColorStride enumify_col_type()
	{
		if constexpr (std::is_same_v<T, glm::vec4>)
		{
			return ColorStride::RGBA;
		}
		else if constexpr (std::is_same_v<T, glm::vec3>)
		{
			return ColorStride::RGB;
		}
		else if constexpr (std::is_same_v<T, std::nullptr_t>)
		{
			return ColorStride::NONE;
		}
		else
		{
			std::cout << "Error: an unknown type was entered for Color Stride!\n";
			return ColorStride::NONE;
		}
	}

	template <GLMVec T>	
	NormalStride enumify_norm_type()
	{
		if constexpr (std::is_same_v<T, glm::vec2>)
		{
			return NormalStride::STRIDE_2D;
		}
		else if constexpr (std::is_same_v<T, glm::vec3>)
		{
			return NormalStride::STRIDE_3D;
		}
		else if constexpr (std::is_same_v<T, std::nullptr_t>)
		{
			return NormalStride::NONE;
		}
		else
		{
			std::cout << "Error: an unknown type was entered for Normal Stride!\n";
			return NormalStride::NONE;
		}
	}

	template <GLMVec T>	
	TextureStride enumify_tex_type()
	{
		if constexpr (std::is_same_v<T, glm::vec2>)
		{
			return TextureStride::STRIDE_2D;
		}
		else if constexpr (std::is_same_v<T, glm::vec3>)
		{
			return TextureStride::STRIDE_3D;
		}
		else if constexpr (std::is_same_v<T, std::nullptr_t>)
		{
			return TextureStride::NONE;
		}
		else
		{
			std::cout << "Error: an unknown type was entered for Texture Stride!\n";
			return TextureStride::NONE;
		}
	}
}