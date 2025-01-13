#pragma once

#include "pch.h"
#include "mesh.h"
#include "vkType\include\std_types.h"

template <vkType::GLMVec POS, vkType::GLMVec COL, vkType::GLMVec NORM, vkType::GLMVec TEX>
class Scene
{
public:

	Scene() = default;


	Scene(Scene&& other) noexcept
		: triangles(std::move(other.triangles))
	{
		other.triangles.clear();

	}

	Scene& operator=(Scene&& other) noexcept
	{
		if (this != &other)
		{
			triangles = std::move(other.triangles);

			other.triangles.clear();
		}
		return *this;
	}


	void initalize()
	{
		for (float x = -1.0f; x < 1.0f; x += 0.2f)
		{

			for (float y = -1.0f; y < 1.0f; y += 0.2f) 
			{
				triangles.push_back(glm::vec3(x, y, 0.0f));
			}
	}

	
	/*std::vector<Mesh<POS, COL, NORM, TEX>>*/ std::vector <glm::vec3> get_triangles()
	{
		return triangles;
	}
	
	~Scene() = default;


private:

	std::vector</*Mesh<POS, COL, NORM, TEX>*/glm::vec3> triangles;
	Mesh<POS, COL, NORM, TEX> mesh; 
};


namespace vkType {

	using scene = Scene<pos, col, norm, tex>;; 

}