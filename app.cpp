#pragma once
#include "app.h"
#include "mesh.h"
#include "stride.h"

using namespace vkVertex;


App::App() = default;



App::App(unsigned int width, unsigned int height, bool debugMode)
{
	numFrames = 0;

	lastTime = 0.0;

	currentTime = 0.0;

	lastTime = 0.0;

	frameTime = 0.0f;

	window = build_glfw_window(width, height, debugMode);

	graphicsEngine = std::make_unique<vkType::engine>(window, ePos, eCol, eNorm, eTex, debugMode);   
}




GLFWwindow* App::build_glfw_window(unsigned int width, unsigned int height, bool debugMode)
{

	//initialize glfw
	if (glfwInit() == GLFW_FALSE)
	{
		std::cerr << "Error Initalizing GLFW! \n";
	}

	//no default rendering client, we'll hook vulkan up
	//to the window later
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	//resizing breaks the swapchain, we'll disable it for now
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	GLFWwindow* glfwWindow = nullptr;

	//GLFWwindow* glfwCreateWindow (int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
	if (glfwWindow = glfwCreateWindow(width, height, "Main", nullptr, nullptr)) 
	{ 
		if (debugMode) 
		{
			std::cout << "Successfully made a GLFW window called \"Main\", width: " << width << ", height: " << height << '\n';
		}
	}
	else 
	{
			std::cout << "GLFW window creation failed\n";
	}

	return glfwWindow;
}




void App::Run() 
{

	std::vector <vkType::vertex> vertices(3);
	 

	vertices[0].initalize({ 1.0f, -0.5f }  ,  { 1.0f, 1.0f, 1.0f });
	vertices[1].initalize({ -1.0f, -0.5f } ,  { 1.0f, 1.0f, 1.0f});
	vertices[2].initalize({ 0.0f,  1.0f }  ,  { 1.0f, 1.0f, 1.0f });


	std::vector<vkType::mesh> meshes(1);
	meshes[0].initialize(vertices);  
	
	std::unique_ptr <vkType::scene> scene = std::make_unique<vkType::scene>();
	scene->initalize();

	std::cout << "\n";
	for (auto& vert : vertices)
	{
		std::cout << " " << vert.position.x << " ";
		std::cout << " " << vert.position.y << " ";
		std::cout << " " << vert.color.x << " ";
		std::cout << " " << vert.color.x << " ";
		std::cout << " " << vert.color.y << " ";
		std::cout << " " << vert.color.z << " ";
		std::cout << "\n";
	}
	graphicsEngine->load_meshes(meshes); 

	std::cout << "\n";
	for (auto& vert : vertices)
	{
		std::cout << " " << vert.position.x << " ";
		std::cout << " " << vert.position.y << " ";
		std::cout << " " << vert.color.x << " ";
		std::cout << " " << vert.color.x << " ";
		std::cout << " " << vert.color.y << " ";
		std::cout << " " << vert.color.z << " ";
		std::cout << "\n";
	}

	graphicsEngine->load_scene(scene); 

	while (!glfwWindowShouldClose(window))
	{ 
		glfwPollEvents();

		graphicsEngine->render();
		graphicsEngine->draw_scene();

		calc_frame_rate();
	}
	
}



void App::calc_frame_rate() { 
	currentTime = glfwGetTime();
	double delta = currentTime - lastTime;

	if (delta >= 1) {
		int framerate{ std::max(1, int(numFrames / delta)) };
		std::stringstream title;
		title << "Running at " << framerate << " fps.";
		glfwSetWindowTitle(window, title.str().c_str());
		lastTime = currentTime;
		numFrames = -1;
		frameTime = float(1000.0 / framerate);
	}

	numFrames++;
}




App::~App()
{

}
