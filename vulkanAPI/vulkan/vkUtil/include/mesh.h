#pragma once

#include "config.h"
#include "stride.h"
#include "vertex.h"
#include "index.h"
#include "std_types.h"



template <GLMVec POS, GLMVec COL, GLMVec NORM, GLMVec TEX>
class Mesh
{
public:

	Mesh() = default;

	Mesh(const std::vector<Vertex<POS, COL, NORM, TEX>>& vertices, const std::vector<vkType::Index>& indices) 
	{ 
		verticesCount = 0;
		indicesCount = 0;
		initalize(vertices, indices);
	}

	Mesh(const Mesh& other)
	{
		verticesCount = other.get_vertices_count();
		indicesCount = other.get_indices_count();
		m_vertices = other.get_vertices(); 
		m_indices = other.get_indices();

	}

	Mesh& operator=(const Mesh& other) 
	{
		if (this != &other) 
		{ 
			verticesCount = other.get_vertices_count(); 
			indicesCount = other.get_indices_count(); 
			m_vertices = other.get_vertices();  
			m_indices = other.get_indices(); 
		}
		return *this;
	}

	Mesh(Mesh&& other)
	{
		verticesCount = std::move(other.get_vertices_count());
		indicesCount = std::move(other.get_indices_count());
		m_vertices = std::move(other.get_vertices());
		m_indices = std::move(other.get_indices());

	}

	Mesh& operator=(Mesh&& other)
	{
		if (this != &other)
		{
			verticesCount = std::move(other.get_vertices_count()); 
			indicesCount = std::move(other.get_indices_count()); 
			m_vertices = std::move(other.get_vertices()); 
			m_indices = std::move(other.get_indices());  
		}
		return *this;
	}

	//Mesh(POS pos, COL col, NORM norm, TEX tex) = default;

	void initialize(const std::vector<Vertex<POS, COL, NORM, TEX>>& vertices)
	{
		m_vertices = vertices;
		m_indices.clear();
	}


	size_t get_vertices_count() const
	{
		return verticesCount; 
	}


	size_t get_indices_count() const
	{
		return indicesCount;
	}


	size_t vertices_size() const
	{
		return m_vertices.size();
	}


	size_t indices_size() const 
	{
		return m_indices.size();
	}




	void initialize(const std::vector<Vertex<POS, COL, NORM, TEX>>& vertices, const std::vector<vkType::Index>& indices)
	{
		m_vertices = std::move(vertices);  
		m_indices = std::move(indices); 
		verticesCount = m_vertices[0].total_size() * m_vertices.size();
		indicesCount = m_indices.size();
	}

	void emplace_back(const Vertex<POS, COL, NORM, TEX>& vertex, const vkType::Index& index) 
	{
		m_vertices.emplace_back(vertex);
		m_indices.emplace_back(index); 
		verticesCount += m_vertices[0].total_size() * m_vertices.size();
		indicesCount += m_indices.size();
	}
	

	void emplace_back(const Vertex<POS, COL, NORM, TEX>& vertex)
	{
		m_vertices.emplace_back(vertex);
		verticesCount += m_vertices[0].total_size() * m_vertices.size();
	}


	
	void push_back(const Vertex<POS, COL, NORM, TEX>& vertex, const vkType::Index& index) 
	{
		m_vertices.push_back(vertex);
		m_indices.push_back(index); 
		verticesCount += m_vertices[0].total_size() * m_vertices.size();
		indicesCount += m_indices.size();
	}
	

	void push_back(const Vertex<POS, COL, NORM, TEX>& vertex)
	{
		m_vertices.push_back(vertex);	 
		verticesCount += m_vertices[0].total_size() * m_vertices.size();
	}


	std::vector <Vertex<POS, COL, NORM, TEX>> get_vertices() const
	{
		return m_vertices;
	}

	std::vector <vkType::Index> get_indices() const
	{
		return m_indices;
	}


	std::vector <float> get_vertices_raw() const
	{
		std::vector<float> verticesRaw; 
		verticesRaw.reserve(verticesCount);

		for (const auto& vertex : m_vertices)
		{
			const float* data = glm::value_ptr(vertex.position);
			verticesRaw.insert(verticesRaw.end(), data, data + vertex.pos_size());

			data = glm::value_ptr(vertex.color);
			verticesRaw.insert(verticesRaw.end(), data, data + vertex.col_size());

			if constexpr (!std::is_same_v<NORM, std::nullptr_t>)
			{
				data = glm::value_ptr(vertex.normal);
				verticesRaw.insert(verticesRaw.end(), data, data + vertex.norm_size());
			}

			if constexpr (!std::is_same_v<TEX, std::nullptr_t>)
			{
				data = glm::value_ptr(vertex.texture);
				verticesRaw.insert(verticesRaw.end(), data, data + vertex.tex_size());
			}
		}

		return verticesRaw; 
	}



	void clear()
	{
		m_vertices.clear();

		m_indices.clear();
	}


	~Mesh()
	{
		clear();
	}


private:
	
	size_t verticesCount;
	size_t indicesCount;

	std::vector<Vertex<POS, COL, NORM, TEX>> m_vertices;
	std::vector <vkType::Index> m_indices;
};



template <GLMVec POS, GLMVec COL>
using Mesh2D = Mesh<POS, COL, std::nullptr_t, std::nullptr_t>; 



template <Struct Parameter>  
using SMesh = Mesh <typename Parameter::Position, typename Parameter::Color, 
					typename Parameter::Normal, typename Parameter::Texture>;


namespace vkType {

	using mesh = Mesh<pos, col, norm, tex>;

}