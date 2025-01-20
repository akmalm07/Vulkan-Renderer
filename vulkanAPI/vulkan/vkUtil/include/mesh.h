#pragma once

#include "config.h"
#include "vkUtil\include\stride.h"
#include "vkUtil\include\vertex.h"



class MeshT
{
public:

	MeshT();

	MeshT(std::vector<vkType::Vert>& vertices, std::vector<vkType::Index>& indices);

	MeshT(const MeshT& other);

	MeshT& operator=(const MeshT& other);

	MeshT(MeshT&& other);

	MeshT& operator=(MeshT&& other);

	//MeshT(POS pos, COL col, NORM norm, TEX tex) = default;

	void initialize(std::vector<vkType::Vert>& vertices);


	void initialize(std::vector<vkType::Vert>& vertices, std::vector<vkType::Index>& indices);

	size_t get_vert_count() const;

	size_t get_ind_count() const;

	size_t vert_size() const;

	size_t ind_size() const;


	void insert(std::vector<vkType::Vert>& vertices, std::vector<vkType::Index>& indices);


	void insert(std::vector<vkType::Vert>& vertices);

	
	void push_back(const vkType::Vert& vertex, const vkType::Index& index);
	

	void push_back(const vkType::Vert& vertex);


	std::vector <vkType::Vert> get_vertices() const;

	std::vector <vkType::Index> get_indices() const;

	void clear();


	~MeshT();

private:
	
	size_t _verticesCount;
	size_t _indicesCount;

	std::vector<vkType::Vert> _vertices;
	std::vector <vkType::Index> _indices;
};



using Mesh = MeshT;
