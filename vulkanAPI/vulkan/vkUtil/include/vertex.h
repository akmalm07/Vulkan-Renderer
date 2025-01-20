#pragma once

#include "config.h"





template <vkType::GLMVec POS, vkType::GLMVec COL, vkType::GLMVec NORM, vkType::GLMVec TEX>
struct VertexT
{
	POS position;
	COL color;
	NORM normal;
	TEX texture;

	VertexT() = default;

	VertexT(const auto& p, const auto& c, const auto& n, const auto& t)
		: position(p), color(c), normal(n), texture(t) {}


	void initalize(const POS& p, const COL& c, const NORM& n, const TEX& t)
	{
		position = p;
		color = c;
		normal = n;
		texture = t;
	}


	//size_t pos_size() const 
	//{
	//	return sizeof(POS) / sizeof(float);
	//}

	//size_t col_size()const
	//{
	//	return sizeof(COL) / sizeof(float);
	//}

	//size_t norm_size()const
	//{
	//	return sizeof(NORM) / sizeof(float);
	//}

	//size_t tex_size()const
	//{
	//	return sizeof(TEX) / sizeof(float);
	//}


	//size_t total_size()
	//{
	//	return pos_size() + col_size() + norm_size() + tex_size();
	//}

};

template <vkType::GLMVec POS, vkType::GLMVec COL>
struct VertexT <POS, COL, std::nullptr_t, std::nullptr_t>
{
	POS position;
	COL color;

	VertexT() = default;

	VertexT(const auto& p, const auto& c) 
		: position(p), color(c) {}


	void initalize(const POS& p, const COL& c)
	{
		position = p; 
		color = c;
	}

	//size_t pos_size() const
	//{
	//	return sizeof(POS) / sizeof(float);
	//}

	//size_t col_size() const
	//{
	//	return sizeof(COL) / sizeof(float); 
	//}


	//size_t total_size()const
	//{
	//	return pos_size() + col_size();
	//}

};


template <vkType::GLMVec POS, vkType::GLMVec COL, vkType::GLMVec NORM>
struct VertexT <POS, COL, NORM, std::nullptr_t>
{
	POS position;
	COL color;
	NORM normal;

	VertexT() = default;

	VertexT(const auto & p, const auto & c, const auto & n)
		: position(p), color(c), normal(n) {}


	void initalize(const POS& p, const COL& c, const NORM& n)
	{
		position = p;
		color = c;
		normal = n;
	}

	//size_t pos_size()const
	//{
	//	return sizeof(POS) / sizeof(float);
	//}

	//size_t col_size()const
	//{
	//	return sizeof(COL) / sizeof(float);
	//}

	//size_t norm_size() const
	//{
	//		
	//	return sizeof(NORM) / sizeof(float);
	//}

	//size_t total_size()
	//{
	//	return pos_size() + col_size() + norm_size(); 
	//}

}; 


template <vkType::GLMVec POS, vkType::GLMVec COL, vkType::GLMVec TEX>
struct VertexT <POS, COL, std::nullptr_t, TEX>
{
	POS position;
	COL color;
	TEX texture;

	VertexT() = default;

	VertexT(const auto& p, const auto& c, const auto& t)
		: position(p), color(c), texture(t) {}


	void initalize(const POS& p, const COL& c, const TEX& t)
	{
		position = p;
		color = c;
		texture = t;
	}

	// Implement conversion logic here
	operator unsigned short() const {
		// Implement conversion logic here
		static_assert(false, "Conversion not implemented");
	}
};

	//size_t pos_size()const
	//{
	//	return sizeof(POS) / sizeof(float);
	//}

	//size_t col_size()const
	//{
	//	return sizeof(COL) / sizeof(float);
	//}

	//size_t tex_size()const
	//{
	//	return sizeof(TEX) / sizeof(float);
	//}


	//size_t total_size()
	//{
	//	return pos_size() + col_size() + tex_size(); 
	//}





namespace vkType
{
	using Vert = VertexT<pos, col, norm, tex>;
}