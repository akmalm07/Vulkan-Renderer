#include "pch.h"

#include "mesh.h"



MeshT::MeshT() = default;

MeshT::MeshT(std::vector<vkType::Vert>& vertices, std::vector<vkType::Index>& indices) :
	_verticesCount(vertices.size()), _indicesCount(indices.size()), _vertices(std::move(vertices)), _indices(std::move(indices))
{}

MeshT::MeshT(const MeshT& other)
{
	_verticesCount = other.get_vert_count();
	_indicesCount = other.get_ind_count();
	_vertices = other.get_vertices();
	_indices = other.get_indices();

}


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

void MeshT::initialize(std::vector<vkType::Vert>& vertices)
{
	_vertices = std::move(vertices);
	_verticesCount = _vertices.size();
	_indices.clear();
}


void MeshT::initialize(std::vector<vkType::Vert>& vertices, std::vector<vkType::Index>& indices)
{
	_vertices = std::move(vertices);
	_indices = std::move(indices);
	_verticesCount = _vertices.size();
	_indicesCount = _indices.size();
}


size_t MeshT::get_vert_count() const { return _verticesCount; }


size_t MeshT::get_ind_count() const { return _indicesCount; }


size_t MeshT::vert_size() const { return _vertices.size() * sizeof(_vertices[0]); }


size_t MeshT::ind_size() const { return _indices.size() * sizeof(_indices[0]); }




void MeshT::insert(std::vector<vkType::Vert>& vertices, std::vector<vkType::Index>& indices)
{
	_vertices.insert(_vertices.end(), std::make_move_iterator(vertices.begin()), std::make_move_iterator(vertices.end()));
	_indices.insert(_indices.end(), std::make_move_iterator(indices.begin()), std::make_move_iterator(indices.end()));
	_verticesCount += vertices.size();
	_indicesCount += indices.size();
}

void MeshT::insert(std::vector<vkType::Vert>& vertices)
{
	_vertices.insert(_vertices.end(), std::make_move_iterator(vertices.begin()), std::make_move_iterator(vertices.end())); 
	_verticesCount = _vertices.size();
}


void MeshT::push_back(const vkType::Vert& vertex, const vkType::Index& index)
{
	_vertices.push_back(vertex);
	_indices.push_back(index);
	_verticesCount++;
	_indicesCount++;
}


void MeshT::push_back(const vkType::Vert& vertex)
{
	_vertices.push_back(vertex);
	_verticesCount++;
}


std::vector <vkType::Vert> MeshT::get_vertices() const
{
	return _vertices;
}

std::vector <vkType::Index> MeshT::get_indices() const
{
	return _indices;
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
