#pragma once

#include "config.h"

#include "vkUtil\include\base_engine.h"
#include "vkUtil\include\mesh.h"
#include "vkUtil\include\VertexBuffer.h"
#include "vkUtil\include\IndexBuffer.h"
#include "vkUtil\include\scene.h"
#include "vkUtil\include\shader.h"




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

	void load_scene(std::unique_ptr<SceneT>& scene);

	void draw_scene(vk::CommandBuffer& cmdBuffer) const	;

	void draw(vk::CommandBuffer& commandBuffer) const override;

	template<vkType::ValidObj T>
	void send_as_push_const(T& data, vk::CommandBuffer cmdBuffer, vkUtil::ShaderStage shader, uint32_t offset) const;

	~Engine() override
	{

	}


private:

	std::unique_ptr <SceneT> _scene; 

	mutable std::unique_ptr<VertexBufferT> _vertexBuffer;    
	mutable std::unique_ptr<IndexBufferT> _indexBuffer;



};


//
//namespace vkType 
//{
//
//	using engine = Engine<pos, col, norm, tex>; 
//}

template<vkType::ValidObj T>
inline void Engine::send_as_push_const(T& data, vk::CommandBuffer cmdBuffer, vkUtil::ShaderStage shader, uint32_t offset) const
{
	cmdBuffer.pushConstants(_vkPipelineLayout, vkUtil::enum_to_vk(shader), offset, sizeof(data), &data); 
}