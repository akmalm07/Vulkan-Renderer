#pragma once

#include "config.h"

#include "vkUtil\include\mesh.h"


class SceneT
{
public:

	SceneT();


	SceneT(SceneT&& other) noexcept;

	SceneT& operator=(SceneT&& other) noexcept;

	
	std::vector <MeshT> get_triangles();
	

	std::vector <UserInput::pos> get_triangles_pos();


	~SceneT();


private:

	std::vector<MeshT> triangles;

	void initalize();
};



namespace vkType
{
	using Scene = SceneT;
}