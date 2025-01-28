#pragma once

#include "config.h"
#include "vkUtil\include\vertex_base.h"

template <vkType::GLMVec POS, vkType::GLMVec COL, vkType::GLMVec NORM, vkType::GLMVec TEX>
struct VertexT;
	

template <vkType::GLM_VEC_TYPE POS, vkType::GLM_VEC_TYPE COL, vkType::GLM_VEC_TYPE NORM, vkType::GLM_VEC_TYPE TEX>
struct VertexT<POS, COL, NORM, TEX> : public PositionFunc<POS>, public ColorFunc<COL>, public NormalFunc<NORM>, public TextureFunc<TEX>
{
public:

	using Pos = PositionFunc<POS>;
	using Col = ColorFunc<COL>;
	using Norm = NormalFunc<NORM>;
	using Tex = TextureFunc<TEX>; 

	using Pos::c_pos_size;
	using Pos::_position;

	using Col::c_col_size;
	using Col::_color;

	using Norm::c_norm_size;
	using Norm::_normal;

	using Tex::c_tex_size;
	using Tex::_texture;



	VertexT() = default;

	VertexT(const POS& p, const COL& c, const NORM& n, const TEX& t)
		: Pos(p), Col(c), Norm(n), Tex(t) {}


	void initalize(const POS& p, const COL& c, const NORM& n, const TEX& t)
	{
		_position = p;
		_color = c;
		_normal = n;
		_texture = t;
	}


	VertexT(const std::initializer_list<vkType::Vertex>& p, const std::initializer_list<vkType::Vertex>& c, const std::initializer_list<vkType::Vertex>& n, const std::initializer_list<vkType::Vertex>& t)
		: Pos(p), Col(c), Norm(n), Tex(t) {}

	void initalize(const std::initializer_list<vkType::Vertex>& p, const std::initializer_list<vkType::Vertex>& c, const std::initializer_list<vkType::Vertex>& n, const std::initializer_list<vkType::Vertex>& t)

	{
		std::copy(p.begin(), p.end(), glm::value_ptr(_position));
		std::copy(c.begin(), c.end(), glm::value_ptr(_color));
		std::copy(n.begin(), n.end(), glm::value_ptr(_normal));
		std::copy(t.begin(), t.end(), glm::value_ptr(_texture));
	}


	std::list<vkType::Vertex> get_raw() const 
	{
		std::list<vkType::Vertex> raw;
		auto pos = Pos::get_pos(); 
		auto col = Col::get_col();
		auto norm= Norm::get_norm();
		auto tex=  Tex::get_tex(); 

		raw.insert(raw.end(), std::make_move_iterator(pos.begin()), std::make_move_iterator(pos.end()));
		raw.insert(raw.end(), std::make_move_iterator(col.begin()), std::make_move_iterator(col.end()));
		raw.insert(raw.end(), std::make_move_iterator(norm.begin()), std::make_move_iterator(norm.end()));
		raw.insert(raw.end(), std::make_move_iterator(tex.begin()), std::make_move_iterator(tex.end()));
		return raw;
	}

	static size_t size() 
	{
		return c_pos_size + c_col_size + c_norm_size + c_tex_size;
	}

	VertexT& operator=(const VertexT& other)
	{
		if (this != &other) {
			_position = other._position;
			_color = other._color;
			_normal = other._normal;
			_texture = other._texture;
		}
		return *this;
	}

	VertexT& operator=(VertexT&& other)
	{
		if (this != &other) {
			_position = std::move(other._position);
			_color = std::move(other._color);
			_normal = other._normal;
			_texture = std::move(other._texture);
		}
		return *this;
	}

	VertexT(const VertexT& other) = default;

	VertexT(VertexT&& other) = default;

};

template <vkType::GLM_VEC_TYPE POS, vkType::GLM_VEC_TYPE COL>
struct VertexT <POS, COL, std::nullptr_t, std::nullptr_t> : public PositionFunc<POS>, public ColorFunc<COL>
{
public:

	using Pos = PositionFunc<POS>;
	using Col = ColorFunc<COL>;


	using Pos::c_pos_size;
	using Pos::_position;

	using Col::c_col_size;
	using Col::_color;


	VertexT() = default;

	VertexT(const POS& p, const COL& c)
		: Pos(p), Col(c) {} 

	void initalize(const POS& p, const COL& c)
	{
		_position = p; 
		_color = c;
	}
	

	VertexT(const std::initializer_list<vkType::Vertex>& p, const std::initializer_list<vkType::Vertex>& c)
		: Pos(p), Col(c) {} 

	void initalize(const std::initializer_list<vkType::Vertex>& p, const std::initializer_list<vkType::Vertex>& c)

	{
		std::copy(p.begin(), p.end(), glm::value_ptr(_position)); 
		std::copy(c.begin(), c.end(), glm::value_ptr(_color));  
	}

	static size_t size() 
	{
		return c_pos_size + c_col_size;
	}


	std::list<vkType::Vertex> get_raw() const
	{
		std::list<vkType::Vertex> raw;
		auto pos = Pos::get_pos();   
		auto col = Col::get_col();  

		raw.insert(raw.end(), std::make_move_iterator(pos.begin()), std::make_move_iterator(pos.end())); 
		raw.insert(raw.end(), std::make_move_iterator(col.begin()), std::make_move_iterator(col.end())); 
		return raw;
	}


	VertexT& operator=(const VertexT& other)
	{
		if (this != &other) {
			_position = other._position;
			_color = other._color;
		}
		return *this;
	}

	VertexT& operator=(VertexT&& other)
	{
		if (this != &other) {
			_position = std::move(other._position);
			_color = std::move(other._color);
		}
		return *this;
	}

	VertexT(const VertexT& other) = default;


	VertexT(VertexT&& other) = default;


};


template <vkType::GLM_VEC_TYPE POS, vkType::GLM_VEC_TYPE COL, vkType::GLM_VEC_TYPE NORM>
struct VertexT <POS, COL, NORM, std::nullptr_t> : public PositionFunc<POS>, public ColorFunc<COL>, public NormalFunc<NORM>
{
public:


	using Pos = PositionFunc<POS>;
	using Col = ColorFunc<COL>;
	using Norm = NormalFunc<NORM>;

	using Pos::c_pos_size;
	using Pos::_position;

	using Col::c_col_size;
	using Col::_color;

	using Norm::c_norm_size;
	using Norm::_normal;


	VertexT() = default;

	VertexT(const POS& p, const COL& c, const NORM& n) 
		: Pos(p), Col(c), Norm(n) {}

	void initalize(const POS& p, const COL& c, const NORM& n)
	{
		_position = p;
		_color = c;
		_normal = n;
	}

	static size_t size() 
	{
		return c_pos_size + c_col_size + c_norm_size;
	}


	VertexT(const std::initializer_list<vkType::Vertex>& p, const std::initializer_list<vkType::Vertex>& c, const std::initializer_list<vkType::Vertex>& n)
		: Pos(p), Col(c), Norm(n) {}

	void initalize(const std::initializer_list<vkType::Vertex>& p, const std::initializer_list<vkType::Vertex>& c, const std::initializer_list<vkType::Vertex>& n)

	{
		std::copy(p.begin(), p.end(), glm::value_ptr(_position));
		std::copy(c.begin(), c.end(), glm::value_ptr(_color));
		std::copy(n.begin(), n.end(), glm::value_ptr(_normal));
	}



	std::list<vkType::Vertex> get_raw()  const
	{
		std::list<vkType::Vertex> raw;
		auto pos =  Pos::get_pos();   
		auto col =  Col::get_col();    
		auto norm = Norm::get_norm();   

		raw.insert(raw.end(), std::make_move_iterator(pos.begin()), std::make_move_iterator(pos.end())); 
		raw.insert(raw.end(), std::make_move_iterator(col.begin()), std::make_move_iterator(col.end())); 
		raw.insert(raw.end(), std::make_move_iterator(norm.begin()), std::make_move_iterator(norm.end())); 
		return raw;
	}


	VertexT& operator=(const VertexT& other)
	{
		if (this != &other) {
			_position = other._position;
			_color = other._color;
			_normal = other._normal;
		}
		return *this;
	}

	VertexT& operator=(VertexT&& other)
	{
		if (this != &other) {
			_position = std::move(other._position);
			_color = std::move(other._color);
			_normal = other._normal;
		}
		return *this;
	}


	VertexT(const VertexT& other) = default;


	VertexT(VertexT&& other) = default;
}; 


template <vkType::GLM_VEC_TYPE POS, vkType::GLM_VEC_TYPE COL, vkType::GLM_VEC_TYPE TEX>
struct VertexT <POS, COL, std::nullptr_t, TEX> : public PositionFunc<POS>, public ColorFunc<COL>, public TextureFunc<TEX>
{
public:


	using Pos = PositionFunc<POS>;
	using Col = ColorFunc<COL>;
	using Tex = TextureFunc<TEX>; 

	using Pos::c_pos_size;
	using Pos::_position;

	using Col::c_col_size;
	using Col::_color;

	using Tex::c_tex_size;
	using Tex::_texture;

	VertexT() = default;
	 
	VertexT(const POS& p, const COL& c, const TEX& t) 
		: Pos(p), Col(c), Tex(t) {}


	void initalize(const POS& p, const COL& c, const TEX& t)
	{
		_position = p;
		_color = c;
		_texture = t;
	}


	VertexT(const std::initializer_list<vkType::Vertex>& p, const std::initializer_list<vkType::Vertex>& c, const std::initializer_list<vkType::Vertex>& t)
		: Pos(p), Col(c), Tex(t) {} 

	void initalize(const std::initializer_list<vkType::Vertex>& p, const std::initializer_list<vkType::Vertex>& c, const std::initializer_list<vkType::Vertex>& t)

	{
		std::copy(p.begin(), p.end(), glm::value_ptr(_position));
		std::copy(c.begin(), c.end(), glm::value_ptr(_color));
		std::copy(t.begin(), t.end(), glm::value_ptr(_texture));
	}

	static size_t size() 
	{
		return c_pos_size + c_col_size + c_tex_size;
	}


	std::list<vkType::Vertex> get_raw() const
	{
		std::list<vkType::Vertex> raw;
		auto pos = Pos::get_pos();      
		auto col = Col::get_col();      
		auto tex = Tex::get_tex();    

		raw.insert(raw.end(), std::make_move_iterator(pos.begin()), std::make_move_iterator(pos.end()));  
		raw.insert(raw.end(), std::make_move_iterator(col.begin()), std::make_move_iterator(col.end())); 
		raw.insert(raw.end(), std::make_move_iterator(tex.begin()), std::make_move_iterator(tex.end()));  
		return raw;
	}

	VertexT& operator=(const VertexT& other)
	{
		if (this != &other) {
			_position = other._position;
			_color = other._color;
			_texture = other._texture;
		}
		return *this;
	}

	VertexT& operator=(VertexT&& other)
	{
		if (this != &other) {
			_position = std::move(other._position); 
			_color = std::move(other._color); 
			_texture = std::move(other._texture);
		}
		return *this;
	}


	VertexT(const VertexT& other) = default;


	VertexT(VertexT&& other) = default;
	
	//operator unsigned short() const
	//{
	//	static_assert(false, "Conversion not implemented");
	//}
};




namespace vkType
{
	using Vert = VertexT<UserInput::pos, UserInput::col, UserInput::norm, UserInput::tex>;
}