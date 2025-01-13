#pragma once

#include "config.h"

#include "std_types.h"



template <GLMVec POS, GLMVec COL, GLMVec NORM, GLMVec TEX>
struct Vertex
{
	POS position;
	COL color;
	NORM normal;
	TEX texture;

	Vertex() = default;

	Vertex(const auto& p, const auto& c, const auto& n, const auto& t)
		: position(p), color(c), normal(n), texture(t) {}


	void initalize(const POS& p, const COL& c, const NORM& n, const TEX& t)
	{
		position = p;
		color = c;
		normal = n;
		texture = t;
	}


	size_t pos_size() const 
	{
		return sizeof(POS) / sizeof(float);
	}

	size_t col_size()const
	{
		return sizeof(COL) / sizeof(float);
	}

	size_t norm_size()const
	{
		return sizeof(NORM) / sizeof(float);
	}

	size_t tex_size()const
	{
		return sizeof(TEX) / sizeof(float);
	}


	size_t total_size()
	{
		return pos_size() + col_size() + norm_size() + tex_size();
	}

};

	template <GLMVec POS, GLMVec COL>
	struct Vertex <POS, COL, std::nullptr_t, std::nullptr_t>
	{
		POS position ;
		COL color ;

		Vertex() = default;

		Vertex(const auto& p, const auto& c) 
			: position(p), color(c) {}


		void initalize(const POS& p, const COL& c)
		{
			position = p; 
			color = c;
		}

		size_t pos_size() const
		{
			return sizeof(POS) / sizeof(float);
		}

		size_t col_size() const
		{
			return sizeof(COL) / sizeof(float); 
		}


		size_t total_size()const
		{
			return pos_size() + col_size();
		}

	};


	template <GLMVec POS, GLMVec COL, GLMVec NORM>
	struct Vertex <POS, COL, NORM, std::nullptr_t>
	{
		POS position;
		COL color;
		NORM normal;

		Vertex() = default;

		Vertex(const auto & p, const auto & c, const auto & n)
			: position(p), color(c), normal(n) {}


		void initalize(const POS& p, const COL& c, const NORM& n)
		{
			position = p;
			color = c;
			normal = n;
		}

		size_t pos_size()const
		{
			return sizeof(POS) / sizeof(float);
		}

		size_t col_size()const
		{
			return sizeof(COL) / sizeof(float);
		}

		size_t norm_size() const
		{
			
			return sizeof(NORM) / sizeof(float);
		}

		size_t total_size()
		{
			return pos_size() + col_size() + norm_size(); 
		}

	}; 


	template <GLMVec POS, GLMVec COL, GLMVec TEX>
	struct Vertex<POS, COL, std::nullptr_t, TEX>
	{
		POS position;
		COL color;
		TEX texture;

		Vertex() = default;

		Vertex(const auto & p, const auto & c, const auto & t)
			: position(p), color(c), texture(t) {} 
	

		void initalize(const POS& p, const COL& c, const TEX& t)
		{
			position = p;
			color = c;
			texture = t;
		}

		size_t pos_size()const
		{
			return sizeof(POS) / sizeof(float);
		}

		size_t col_size()const
		{
			return sizeof(COL) / sizeof(float);
		}

		size_t tex_size()const
		{
			return sizeof(TEX) / sizeof(float);
		}


		size_t total_size()
		{
			return pos_size() + col_size() + tex_size(); 
		}

	};






	template <typename Pos, typename Col>
	using Vertex2D = Vertex<Pos, Col, std::nullptr_t, std::nullptr_t>;


namespace vkType {

	using vertex = Vertex<pos, col, norm, tex>;
}