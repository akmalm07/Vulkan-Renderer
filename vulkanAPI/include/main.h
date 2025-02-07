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

		Vert v1 = { {-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f} };
		Vert v2 = { {0.5f, 0.5f  }, {0.0f, 1.0f, 0.0f} };
		Vert v3 = { {1.0f, -1.0f }, {0.0f, 0.0f, 1.0f} };

		Mesh mesh = { v1, v2, v3 };

		engine.load_mesh(mesh);
		engine.load_scene(std::move(std::make_unique<Scene>()));
		while (engine.running())
		{
			engine.render();
		}
	}
}

