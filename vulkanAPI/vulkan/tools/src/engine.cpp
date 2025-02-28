#include "pch.h"

#include "tools\include\engine.h"
#include "tools\include\descriptor_set_registry.h"


Engine::Engine() : 
	BaseEngine()
{}


Engine::Engine(GLFWwindow* glfwWindow, bool orthoOrperspective, bool debug) :
	BaseEngine(glfwWindow, orthoOrperspective, debug), _scene(nullptr)
{}


Engine::Engine(tools::WindowT& window, bool orthoOrperspective, bool debug) :
	BaseEngine(window, orthoOrperspective, debug), _scene(nullptr)
{}


Engine::Engine(int width, int height, bool orthoOrperspective, bool debug) :
	BaseEngine(width, height, orthoOrperspective, debug), _scene(nullptr)
{}


void Engine::load_mesh(MeshT& mesh) const
{
	std::vector<vkType::Vertex> vertices;

	std::vector<vkType::Index> indices;

	const auto& verts = mesh.get_vertices_raw();

	vertices.insert(vertices.end(), MOVE_ITR(verts.begin()), MOVE_ITR(verts.end()));

	DEBUG_ITERATOR(verts);

	vkUtil::BufferInitInput bufferInfo = {};

	bufferInfo.logicalDevice = _vkLogicalDevice;

	bufferInfo.physicalDevice = _vkPhysicalDevice;

	_vertexBuffer = std::make_unique<VertexBuffer>(bufferInfo);
	_vertexBuffer->initalize(vertices, _debugMode);

	const auto& inds = mesh.get_indices();
	if (!inds.empty()) 
	{
		indices.insert(indices.end(), MOVE_ITR(inds.begin()), MOVE_ITR(inds.end())); 
		_indexBuffer = std::make_unique<IndexBuffer>(bufferInfo);
		_indexBuffer->initalize(indices, _debugMode);
	}
}



void Engine::game_logic(const double& deltaTime)
{

	
}



void Engine::load_meshes(std::vector<MeshT>& meshes) const
{
	size_t indicesSize = 0, verticesSize = 0;

	for (const auto& mesh : meshes)
	{
		verticesSize += mesh.get_vert_count();
		indicesSize += mesh.ind_size();
	}

	std::vector<vkType::Vertex> vertices;
	vertices.reserve(verticesSize);

	std::vector<vkType::Index> indices;
	indices.reserve(indicesSize);

	for (auto& mesh : meshes)
	{
		const auto& verts = mesh.get_vertices_raw();
		vertices.insert(vertices.end(), MOVE_ITR(verts.begin()), MOVE_ITR(verts.end()));
		DEBUG_ITERATOR(verts);
		if (mesh.get_indices().empty())
		{
			continue;
		}
		const auto& inds = mesh.get_indices();
		indices.insert(indices.end(), MOVE_ITR(inds.begin()), MOVE_ITR(inds.end()));
	}



	vkUtil::BufferInitInput bufferInfo = {};

	bufferInfo.logicalDevice = _vkLogicalDevice;

	bufferInfo.physicalDevice = _vkPhysicalDevice;

	_vertexBuffer = std::make_unique<VertexBuffer>(bufferInfo);

	_vertexBuffer->initalize(vertices, _debugMode);

	DEBUG_ITERATOR(vertices);


	if (!indices.empty())
	{
		_indexBuffer = std::make_unique<IndexBuffer>(bufferInfo);
		_indexBuffer->initalize(indices, _debugMode);
	}
}

void Engine::load_meshes(std::vector<vkType::Vertex>& meshes, std::vector<vkType::Index>& indices) const
{

	vkUtil::BufferInitInput bufferInfo = {};

	bufferInfo.logicalDevice = _vkLogicalDevice;

	bufferInfo.physicalDevice = _vkPhysicalDevice;

	_vertexBuffer = std::make_unique<VertexBuffer>(bufferInfo);

	_vertexBuffer->initalize(meshes, _debugMode);

	DEBUG_ITERATOR(meshes); 


	if (!indices.empty()) 
	{
		_indexBuffer = std::make_unique<IndexBuffer>(bufferInfo); 
		_indexBuffer->initalize(indices, _debugMode); 
	}

}




void Engine::load_scene(std::unique_ptr<SceneT> scene)
{
	if (scene)
	{
		_scene = std::move(scene);	
	}
}



void Engine::draw_scene(vk::CommandBuffer& cmdBuffer) const
{
	//For now, we are not using the scene class,
	// so we will just draw the mesh
	//FIX IMMIDIATELY TO DRAW IN THE CORRECT ORDER

	//if (_scene)
	//{
	//	for (const auto& position : _scene->get_triangles_pos())
	//	{ 
	//		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
	//		vkUtil::ObjectData objectData(vkUtil::ShaderStage::VERTEX);
	//		objectData.c_data._model = model;
	//		send_as_push_const(objectData.c_data, cmdBuffer, vkUtil::ShaderStage::VERTEX, 0);
	//	}
	//}

	//vkUtil::ObjectData objectData(vkUtil::ShaderStage::VERTEX);
	//objectData.c_data._model = glm::mat4(1.0f);
	//send_as_push_const(objectData.c_data, cmdBuffer, vkUtil::ShaderStage::VERTEX, 0); 
}


//
//void Engine::load_scene(std::unique_ptr<SceneT>& scene)
//{
//	if (scene)
//	{
//		_scene = std::move(scene);
//	}
//}


void Engine::draw(vk::CommandBuffer& commandBuffer) const
{
	draw_scene(commandBuffer);
	
	bool hasVertBuffer = _vertexBuffer != nullptr; 
	bool hasIndBuffer = (_indexBuffer != nullptr) && (hasVertBuffer); 

	if (_vertexBuffer)
	{
		std::vector<vk::DeviceSize> vertOffset = { 0 };
		_vertexBuffer->bind_buffer(commandBuffer, vertOffset);
	}
	if (hasIndBuffer) 
	{
		_indexBuffer->bind_buffer(commandBuffer, 0);
	}

	call_push_consts();

	if (hasIndBuffer && hasVertBuffer)
	{
		uint32_t indexCount = UINT32(_indexBuffer->index_count()); 
		commandBuffer.drawIndexed(indexCount, 1, 0, 0, 0); 
	}
	else if (hasVertBuffer)
	{
		uint32_t vertCount = UINT32(_vertexBuffer->vertex_count());
		commandBuffer.draw(vertCount, 1, 0, 0);
	}


}

void Engine::update_sets(vk::CommandBuffer& cmdBuff) 
{ 
	//Binding the descriptor set

	cmdBuff.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, _vkPipelineLayout, 0, 1, _vkDescriptorSets.sets.data(), 0, nullptr);



	if(_scene)
	{
		_scene->update_sets(cmdBuff);
	}



	for (const auto& [i, set] : _vkDescriptorSets.updated | std::views::enumerate)
	{
		for (const auto& [j, updated] : set | std::views::enumerate)
		{
			if (updated.status)
			{
				_vkDescriptorSets.updated[i][j].status = false;

				if (updated.get_id() == 0)
				{
					_vkDescriptorSets.updated[SIZET(Sets::Set1)][SIZET(Set1::Binding1)].status = false;
					vkUtil::update_buffer(
						_vkLogicalDevice,
						_vkDescriptorSetBuffers[SIZET(Buffer1)].bufferMemory,
						_MVPMats
					);
				}

				vk::DescriptorBufferInfo bufferInfo;
				bufferInfo.buffer = _vkDescriptorSetBuffers[SIZET(Buffer1)].buffer;
				bufferInfo.offset = 0;
				bufferInfo.range = sizeof(_MVPMats);

				vk::WriteDescriptorSet writeDescriptorSet;
				writeDescriptorSet.descriptorType = vk::DescriptorType::eUniformBuffer;
				writeDescriptorSet.descriptorCount = 1;
				writeDescriptorSet.dstBinding = 0;
				writeDescriptorSet.dstArrayElement = 0;
				writeDescriptorSet.dstSet = _vkDescriptorSets.sets[SIZET(Sets::Set1)];
				writeDescriptorSet.pBufferInfo = &bufferInfo;
				writeDescriptorSet.pImageInfo = nullptr;
				writeDescriptorSet.pTexelBufferView = nullptr;

				_vkLogicalDevice.updateDescriptorSets(1, &writeDescriptorSet, 0, nullptr);

			}
		}
	}
}

Engine::~Engine()

{
	_vkLogicalDevice.waitIdle();

	_vkGraphicsQueue.waitIdle();

	_vertexBuffer.reset();
	_indexBuffer.reset();
	_scene.reset();
	
}


void Engine::call_push_consts() const
{
	for (const auto& pushConst : _pushConstCalls)
	{
		pushConst();
	}
	_pushConstCalls.clear();
}


bool Engine::camera_logic()
{
	_window.WaitInitallyForSignal();

	bool running = !_window.GetShouldClose();

	while (running)
	{
		running = !_window.GetShouldClose();

		if (_window.IsOneInputActive())
		{
			std::cout << "Delta Time: " << _deltaTime << std::endl;
			using tools::Keys;
			using tools::Mods;


			const std::array<bool, 1024>& keys = _window.GetKeysConstRef();

			Keys movekey;

			if (keys[SIZET(Keys::W)])
			{
				movekey = Keys::W;
			}
			else if (keys[SIZET(Keys::S)])
			{
				std::cout << "i CHECKED IT TO FIRST\n";
				movekey = Keys::S;
			}
			else if (keys[SIZET(Keys::A)])
			{
				movekey = Keys::A;
			}
			else if (keys[SIZET(Keys::D)])
			{
				movekey = Keys::D;
			}
			else if (keys[SIZET(Keys::Q)])
			{
				movekey = Keys::Q;
			}
			else if (keys[SIZET(Keys::E)])
			{
				movekey = Keys::E;
			}
			else
			{
				_window.AllowWindowToContinueAndWait();
				continue;
			}


			if (_window.NumOfKeysInList(movekey) == 1)
			{
				_window.FindKeyComb(movekey)->change_parameters(_deltaTime);

			}
			else if (_window.NumOfKeysInList(movekey) > 1)
			{
				for (auto& key : _window.FindKeyCombList(movekey))
				{
					key->change_parameters(_deltaTime);
				}
			}
				_vkDescriptorSets.updated[SIZET(Sets::Set1)][SIZET(Set1::Binding1)].status = true;



			Keys turnkey;
			if (keys[SIZET(Keys::Up)])
			{
				turnkey = Keys::Up;
			}
			else if (keys[SIZET(Keys::Down)])
			{
				turnkey = Keys::Down;
			}
			else if (keys[SIZET(Keys::Right)])
			{
				turnkey = Keys::Right;
			}
			else if (keys[SIZET(Keys::Left)])
			{
				turnkey = Keys::Left;
			}
			else
			{
				_window.AllowWindowToContinueAndWait();
				continue;
			}
			
			if (_window.NumOfKeysInList(movekey) == 1)
			{
				_window.FindKeyComb(movekey)->change_parameters(0.3, 0.3, _deltaTime);

			}
			else if (_window.NumOfKeysInList(movekey) < 1)
			{
				for (auto& key : _window.FindKeyCombList(movekey))
				{
					key->change_parameters(0.3, 0.3, _deltaTime);
				}
			}
		}		
	}

	return true;
}
