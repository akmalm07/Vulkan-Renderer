#pragma once

#include "config.h"
#include "tools\include\engine.h"
#include "vkUtil\include\mesh.h"
#include "vkUtil\include\vertex.h"

#include <memory>

namespace GameRenderer
{
	using namespace vkType;

	void Run()
	{
		Engine engine;

		Vert v1 = { {-1.0f/8, -1.0f/8, 0.0f }, {1.0f, 0.0f, 0.0f} };
		Vert v2 = { {1.0f /8, -1.0f/8, 0.0f }, {0.0f, 1.0f, 0.0f} };
		Vert v3 = { {0.0f /8,  1.0f/8, 0.0f }, {0.0f, 0.0f, 1.0f} };

		std::vector<float> vertices = {
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  // 0 - Bottom-left-front
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,// 1 - Bottom-right-front
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,// 2 - Top-right-front
			-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 3 - Top-left-front
			-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 4 - Bottom-left-back
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, // 5 - Bottom-right-back
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 6 - Top-right-back
			-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f // 7 - Top-left-back
		};

		std::vector<uint16_t> indices = {
			// Front face
			0, 1, 2,  0, 2, 3,

			// Back face
			4, 5, 6,  4, 6, 7,

			// Left face
			0, 3, 7,  0, 7, 4,

			// Right face
			1, 2, 6,  1, 6, 5,

			// Bottom face
			0, 1, 5,  0, 5, 4,

			// Top face
			3, 2, 6,  3, 6, 7
		};
		engine.load_meshes(vertices, indices); 
		//engine.load_scene(std::move(std::make_unique<Scene>()));
		while (engine.running())
		{
			engine.render();
		}
	}
}

