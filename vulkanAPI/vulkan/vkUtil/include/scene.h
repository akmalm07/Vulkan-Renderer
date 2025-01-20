#pragma once

#include "config.h"

#include "vkUtil\include\mesh.h"


template <vkType::GLMVec POS, vkType::GLMVec COL, vkType::GLMVec NORM, vkType::GLMVec TEX>
class SceneT
{
public:

	SceneT() = default;


	SceneT(SceneT&& other) noexcept
		: triangles(std::move(other.triangles))
	{
		other.triangles.clear();

	}

	SceneT& operator=(SceneT&& other) noexcept
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
	}
	
	/*std::vector<Mesh<POS, COL, NORM, TEX>>*/ std::vector <glm::vec3> get_triangles()
	{
		return triangles;
	}
	
	~SceneT() = default;


private:

	std::vector<Mesh> triangles;
};



using Scene = SceneT<pos, col, norm, tex>;

