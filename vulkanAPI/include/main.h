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


		std::vector<float> vertices = {
	0.0f,  1.0f, -2.0f, 1.0f, 0.0f, 0.0f, 
	-1.0f, -1.0f, -2.0f, 0.0f, 1.0f, 0.0f,
	1.0f, -1.0f, -2.0f, 0.0f, 0.0f, 1.0f
		};

		std::vector<uint16_t> indices = {

			// Front face
			0, 1, 2, 2, 3, 0,
			
			// Back face
			4, 5, 6, 6, 7, 4,
			
			// Right face
			1, 5, 6, 6, 2, 1,
			
			// Left face
			4, 0, 3, 3, 7, 4,
			
			// Top face
			3, 2, 6, 6, 7, 3,
			
			// Bottom face
			4, 5, 1, 1, 0, 4,

		};
		engine.load_meshes(vertices, indices); 
		//engine.load_scene(std::move(std::make_unique<Scene>()));
		while (engine.running())
		{
			engine.render();
		}
	}
}

