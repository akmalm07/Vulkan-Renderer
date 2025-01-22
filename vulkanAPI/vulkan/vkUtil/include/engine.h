#pragma once

#include "config.h"

#include "vkUtil\include\base_engine.h"
#include "vkUtil\include\mesh.h"
#include "vkUtil\include\VertexBuffer.h"
#include "vkUtil\include\IndexBuffer.h"
#include "vkUtil\include\scene.h"




namespace vkUtil {
	struct SwapChainFrame;
}




class Engine : public BaseEngine  
{
public:

	Engine();

	Engine(vkVert::StrideBundle stride, int width, int height, bool debug);


	Engine(GLFWwindow* glfwWindow, vkVert::StrideBundle stride, bool debug);

	void load_meshes(std::vector<MeshT>& meshes) const;

	//void load_scene(std::unique_ptr<Scene>& scene);

	void draw_scene()
	{
		
	}


	void draw(vk::CommandBuffer& commandBuffer) const override;


	~Engine() override
	{

	}


private:

	//std::unique_ptr <Scene> _scene; 

	mutable std::unique_ptr<VertexBuffer> _vertexBuffer;    
	mutable std::unique_ptr<IndexBuffer> _indexBuffer;


};


//
//namespace vkType 
//{
//
//	using engine = Engine<pos, col, norm, tex>; 
//}
