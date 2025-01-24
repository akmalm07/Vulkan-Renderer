#pragma once

#include "config.h"

namespace glm
{
	template<vkType::GLMVec T>
	struct vec_size
	{
		static constexpr size_t value = sizeof(T) / sizeof(typename T::value_type);
	};

	template<vkType::GLMVec T>
	constexpr size_t vec_size_v = vec_size<T>::value; 
	

	template<size_t S, class T>
	std::array<Vertex, S> get_arr(const T& t)
	{
		std::array<Vertex, S> arr;
		for (size_t i = 0; i < S; i++)
		{
			arr[i] = t[i];
		}
		return arr;
	}
}


template <vkType::GLMVec T>
struct PositionFunc
{
	static constexpr size_t c_pos_size = glm::vec_size_v<T>; 
	T _position;

	PositionFunc() = default;
	PositionFunc(const T& pos) : _position(pos) {}
	PositionFunc(const std::initializer_list<Vertex>& pos) { std::copy(pos.begin(), pos.end(), glm::value_ptr(_position)); }

	std::array<Vertex, c_pos_size> get_pos() const 
	{
		return glm::get_arr<c_pos_size>(_position);
	}
};

template <vkType::GLMVec T>
struct ColorFunc
{
	static constexpr size_t c_col_size = glm::vec_size_v<T>; 
	T _color; 

	ColorFunc() = default;
	ColorFunc(const T& col) : _color(col) {}
	ColorFunc(const std::initializer_list<Vertex>& col) { std::copy(col.begin(), col.end(), glm::value_ptr(_color)); }

	std::array<Vertex, c_col_size> get_col() const
	{
		return glm::get_arr<c_col_size>(_color); 
	}
};

template <vkType::GLMVec T>
struct NormalFunc {
	static constexpr size_t c_norm_size = glm::vec_size_v<T>;
	T _normal;

	NormalFunc() = default;
	NormalFunc(const T& norm) : _normal(norm) {}
	NormalFunc(const std::initializer_list<Vertex>& norm) { std::copy(norm.begin(), norm.end(), glm::value_ptr(_normal)); }

	std::array<Vertex, c_norm_size> get_norm() const
	{
		return glm::get_arr<c_norm_size>(_normal);
	}
};

template <vkType::GLMVec T>
struct TextureFunc {
	static constexpr size_t c_tex_size = glm::vec_size_v<T>;
	T _texture;

	TextureFunc() = default;
	TextureFunc(const T& tex) : _texture(tex) {}
	TextureFunc(const std::initializer_list<Vertex>& tex) { std::copy(tex.begin(), tex.end(), glm::value_ptr(_texture)); }

	std::array<Vertex, c_tex_size> get_tex() const
	{
		return glm::get_arr<c_tex_size>(_texture);
	}
};
