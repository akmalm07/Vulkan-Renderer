#pragma once

#include "config.h"
#include "vkUtil\include\engine.h"
#include "vkUtil\include\mesh.h"
#include "vkUtil\include\vertex.h"

namespace GameRenderer
{
	using namespace vkType;

	void Run()
	{
		Engine engine;

		Vert v1 = { {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}};
		Vert v2 = { {0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}};
		Vert v3 = { {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}};

		Mesh mesh = { v1, v2, v3 };

		std::vector<Mesh> meshes;
		meshes.push_back(mesh);

		engine.load_meshes(meshes);

		engine.render();
	}
}

