#pragma once

#include "config.h"
#include "engine.h"
#include "timer.h"
#include "scene.h"
#include "definitions.h"
#include "vertex.h"

#include "std_types.h"
#include "engine.h"

class App
{
public:

	App();

	App(unsigned int width, unsigned int height, bool debugMode);

	GLFWwindow* build_glfw_window(unsigned int width, unsigned int height, bool debugMode);

	void Run();

	void calc_frame_rate();


	~App();


private:




	vkVertex::PosStride ePos =     vkType::enumify_pos_type<pos>();
	vkVertex::ColorStride eCol =   vkType::enumify_col_type<col>(); 
	vkVertex::NormalStride eNorm = vkType::enumify_norm_type<norm>(); 
	vkVertex::TextureStride eTex = vkType::enumify_tex_type<tex>(); 

	
	std::unique_ptr <vkType::engine> graphicsEngine;

	GLFWwindow* window;

	double lastTime, currentTime;

	float frameTime;

	int numFrames;


};

