#pragma once

#include "config.h"

#include "tools\include\base_engine.h"

#include "vkUtil\include\mesh.h"
#include "vkUtil\include\VertexBuffer.h"
#include "vkUtil\include\IndexBuffer.h"
#include "tools\include\scene.h"
#include "vkUtil\include\shader_bundles.h"
#include "vkInit\include\descriptor_set_bundles.h"
#include "tools\include\memory_pool.h"

#include <queue>



namespace vkUtil {
	struct SwapChainFrame;
}




class Engine : public BaseEngine
{
public:

	Engine();

	Engine(int width, int height, bool orthoOrperspective, bool debug);

	Engine(tools::WindowT& window, bool orthoOrperspective, bool debug);

	Engine(GLFWwindow* glfwWindow, bool orthoOrperspective, bool debug);

	void load_meshes(std::vector<MeshT>& meshes) const;
	
	void load_meshes(std::vector<vkType::Vertex>& meshes, std::vector<vkType::Index>& indices) const;

	void load_mesh(MeshT& mesh) const;

	void game_logic(const double& deltaTime) override;

	void camera_logic() override;

	void load_scene(std::unique_ptr<SceneT> scene);

	void draw_scene(vk::CommandBuffer& cmdBuffer) const;

	void draw(vk::CommandBuffer& commandBuffer) const override; 

	void update_sets() override;


	template<vkType::ValidObj T>
	void send_as_push_const(T& data, vk::CommandBuffer& cmdBuffer, vkUtil::ShaderStage shader, uint32_t offset) const;

	~Engine() override;


private:

	mutable std::vector<std::function<void()>> _pushConstCalls;  

	std::unique_ptr <SceneT> _scene; 

	mutable std::unique_ptr<VertexBufferT> _vertexBuffer;    
	mutable std::unique_ptr<IndexBufferT> _indexBuffer;

private:
	void call_push_consts() const;
};


//
//namespace vkType 
//{
//
//	using engine = Engine<pos, col, norm, tex>; 
//}

template<vkType::ValidObj T> 
inline void Engine::send_as_push_const(T& data, vk::CommandBuffer& cmdBuffer, vkUtil::ShaderStage shader, uint32_t offset) const
{
	_pushConstCalls.emplace_back([this, &cmdBuffer, shader, offset, &data]()   
		{ cmdBuffer.pushConstants(_vkPipelineLayout, vkUtil::enum_to_vk(shader), offset, sizeof(data), &data); });  
}
