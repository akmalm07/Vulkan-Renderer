#include "headers.h"

#include "vkUtil\include\mesh.h"



MeshT::MeshT() = default;

MeshT::MeshT(std::list<vkType::Vert>& vertices, std::list<vkType::Index>& indices) :
	_verticesCount(vertices.size()), _indicesCount(indices.size()), _vertices(std::move(vertices)), _indices(std::move(indices))
{}

MeshT::MeshT(std::list<vkType::Vert>& vertices) : 
	_verticesCount(vertices.size()), _indicesCount(0), _vertices(std::move(vertices))
{}


MeshT::MeshT(vkType::Vert vertex)
{
	_vertices.push_back(vertex);
	_verticesCount = 1;
	_indicesCount = 0;

}


MeshT::MeshT(vkType::Vert vertex, vkType::Index index)
{
	_vertices.push_back(vertex);  
	_indices.push_back(index); 
	_verticesCount = 1;  
	_indicesCount = 1; 

}



MeshT::MeshT(const MeshT& other)
{
	_verticesCount = other.get_vert_count();
	_indicesCount = other.get_ind_count();
	_vertices = other.get_vertices();
	_indices = other.get_indices();

}

MeshT::MeshT(std::initializer_list<vkType::Vert> verts) : 
	_vertices(verts), _verticesCount(verts.size()) 
{}

MeshT::MeshT(std::initializer_list<vkType::Vert> verts, std::initializer_list<vkType::Index> inds) 
	: _vertices(verts), _verticesCount(verts.size()), _indices(inds), _indicesCount(inds.size()) 
{}


MeshT& MeshT::operator=(const MeshT& other)
{
	if (this != &other)
	{
		_verticesCount = other.get_vert_count();
		_indicesCount = other.get_ind_count();
		_vertices = other.get_vertices();
		_indices = other.get_indices();
	}
	return *this;
}

MeshT::MeshT(MeshT&& other)
{
	_verticesCount = std::move(other.get_vert_count());
	_indicesCount = std::move(other.get_ind_count());
	_vertices = std::move(other.get_vertices());
	_indices = std::move(other.get_indices());

}

MeshT& MeshT::operator=(MeshT&& other)
{
	if (this != &other)
	{
		_verticesCount = std::move(other.get_vert_count());
		_indicesCount = std::move(other.get_ind_count());
		_vertices = std::move(other.get_vertices());
		_indices = std::move(other.get_indices());
	}
	return *this;
}

//MeshT(POS pos, COL col, NORM norm, TEX tex) = default;

void MeshT::initialize(std::list<vkType::Vert>& vertices)
{
	_vertices = std::move(vertices);
	_verticesCount = _vertices.size();
	_indices.clear();
}


void MeshT::initialize(std::list<vkType::Vert>& vertices, std::list<vkType::Index>& indices)
{
	_vertices = std::move(vertices);
	_indices = std::move(indices);
	_verticesCount = _vertices.size();
	_indicesCount = _indices.size();
}


size_t MeshT::get_vert_count() const { return _verticesCount; }


size_t MeshT::get_ind_count() const { return _indicesCount; }


size_t MeshT::vert_size() const 
{
	if (_vertices.empty())
	{
		return 0;
	}
	return _verticesCount * _vertices.front().size(); 
}


size_t MeshT::ind_size() const 
{
	if (_indices.empty())
	{
		return 0;
	}
	return _indicesCount * sizeof(_indices.front());
}



void MeshT::insert(std::list<vkType::Vert>& vertices, std::list<vkType::Index>& indices)
{
	_vertices.insert(_vertices.end(), MOVE_ITR(vertices.begin()), MOVE_ITR(vertices.end()));
	_indices.insert(_indices.end(), MOVE_ITR(indices.begin()), MOVE_ITR(indices.end()));
	_verticesCount += vertices.size();
	_indicesCount += indices.size();
}

void MeshT::insert(std::list<vkType::Vert>& vertices)
{
	_vertices.insert(_vertices.end(), MOVE_ITR(vertices.begin()), MOVE_ITR(vertices.end())); 
	_verticesCount = _vertices.size();
}


void MeshT::push_back(const vkType::Vert& vertex, const vkType::Index& index)
{
	_vertices.push_back(std::move(vertex));
	_indices.push_back(std::move(index));
	_verticesCount++;
	_indicesCount++;
}


void MeshT::push_back(const vkType::Vert& vertex)
{
	_vertices.push_back(std::move(vertex));
	_verticesCount++;
}


void MeshT::push_front(const vkType::Vert& vertex, const vkType::Index& index)
{
	_vertices.push_front(std::move(vertex));
	_indices.push_front(std::move(index));
	_verticesCount++;
	_indicesCount++;
}


void MeshT::push_front(const vkType::Vert& vertex)
{
	_vertices.push_front(std::move(vertex));
	_verticesCount++;
}


std::list <vkType::Vert> MeshT::get_vertices() const
{
	return _vertices;
}

std::list <vkType::Index> MeshT::get_indices() const
{
	return _indices;
}


std::list <vkType::Vertex> MeshT::get_vertices_raw() const	
{
	std::list<vkType::Vertex> raw;
	for (const auto& vertex : _vertices)
	{
		const auto& vert = vertex.get_raw();
		raw.insert(raw.end(), MOVE_ITR(vert.begin()), MOVE_ITR(vert.end()));
	}

	return raw;
}


void MeshT::clear()
{
	_vertices.clear();

	_indices.clear();
}


MeshT::~MeshT()
{
	clear();
}
