#pragma once

#include "config.h"
#include "tools\include\stride.h"
#include "vkUtil\include\vertex.h"



class MeshT
{
public:

	MeshT();

	MeshT(std::list<vkType::Vert>& vertices, std::list<vkType::Index>& indices);
	MeshT(std::list<vkType::Vert>& vertices);

	MeshT(vkType::Vert vertex);

	MeshT(vkType::Vert vertex, vkType::Index index);

	MeshT(std::initializer_list<vkType::Vert> verts);
	MeshT(std::initializer_list<vkType::Vert> verts, std::initializer_list<vkType::Index> inds);

	MeshT(const MeshT& other);

	MeshT& operator=(const MeshT& other);

	MeshT(MeshT&& other);

	MeshT& operator=(MeshT&& other);

	//MeshT(POS pos, COL col, NORM norm, TEX tex) = default;

	void initialize(std::list<vkType::Vert>& vertices);

	void initialize(std::list<vkType::Vert>& vertices, std::list<vkType::Index>& indices);

	size_t get_vert_count() const;

	size_t get_ind_count() const;

	size_t vert_size() const;

	size_t ind_size() const;


	void push_front(const vkType::Vert& vertex, const vkType::Index& index);

	void push_front(const vkType::Vert& vertex);

	void insert(std::list<vkType::Vert>& vertices, std::list<vkType::Index>& indices);

	void insert(std::list<vkType::Vert>& vertices);

	void push_back(const vkType::Vert& vertex, const vkType::Index& index);
	

	void push_back(const vkType::Vert& vertex);


	std::list <vkType::Vert> get_vertices() const;

	std::list <vkType::Index> get_indices() const;


	std::list <vkType::Vertex> get_vertices_raw() const;

	void clear();


	~MeshT();

private:
	
	size_t _verticesCount;
	size_t _indicesCount;

	std::list<vkType::Vert> _vertices;
	std::list<vkType::Index> _indices;
};


namespace vkType
{
	using Mesh = MeshT;
}



