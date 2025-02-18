#include "pch.h"

#include "tools\include\engine.h"
#include "tools\include\descriptor_set_registry.h"


Engine::Engine() : 
	BaseEngine()
{}


Engine::Engine(GLFWwindow* glfwWindow, vkVert::StrideBundle stride, bool orthoOrperspective, bool debug) :
	BaseEngine(glfwWindow, stride, orthoOrperspective, debug), _scene(nullptr)
{}



Engine::Engine(vkVert::StrideBundle stride, int width, int height, bool orthoOrperspective, bool debug) :
	BaseEngine(stride, width, height, orthoOrperspective, debug), _scene(nullptr)
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

		/*		for (const auto& vert : vertices)
				{
					std::cout << " " << vert << " ";
				}
				std::cout << "\n";
				std::cout << "SIZE: " << vertices.size() << "\n";
				*/
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



	for (auto&& [i, set] : _vkDescriptorSets.updated | std::views::enumerate)
	{
		if (set)
		{
			_vkDescriptorSets.updated[i] = false;

			vk::DescriptorBufferInfo bufferInfo;
			bufferInfo.buffer = _vkDescriptorSetBuffers[SIZET(Buffer1)].buffer;
			bufferInfo.offset = 0;
			bufferInfo.range = sizeof(_modelMat);

			vk::WriteDescriptorSet writeDescriptorSet;

			writeDescriptorSet.descriptorType = vk::DescriptorType::eUniformBuffer;
			writeDescriptorSet.descriptorCount = 1;
			writeDescriptorSet.dstBinding = 0;
			writeDescriptorSet.dstArrayElement = 0;
			writeDescriptorSet.dstSet = _vkDescriptorSets.sets[SIZET(Set1)];
			writeDescriptorSet.pBufferInfo = &bufferInfo;
			writeDescriptorSet.pImageInfo = nullptr;
			writeDescriptorSet.pTexelBufferView = nullptr;

			_vkLogicalDevice.updateDescriptorSets(1, &writeDescriptorSet, 0, nullptr);

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




//template class Engine <glm::vec2, glm::vec3, nullptr_t, nullptr_t>;  
//template class Engine <glm::vec3, glm::vec3, nullptr_t, nullptr_t>;  
//template class Engine <glm::vec3, glm::vec4, nullptr_t, nullptr_t>;  
