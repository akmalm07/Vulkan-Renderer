#include "pch.h"

#include "engine.h"


Engine::Engine() : 
	BaseEngine()
{}


Engine::Engine(GLFWwindow* glfwWindow, vkVert::StrideBundle stride, bool debug) :
	BaseEngine(glfwWindow, stride, debug)
{}



Engine::Engine(vkVert::StrideBundle stride, int width, int height, bool debug) :
	BaseEngine(stride, width, height, debug) 
{}


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
		vertices.insert(vertices.end(), std::make_move_iterator(verts.begin()), std::make_move_iterator(verts.end()));

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
		indices.insert(indices.end(), std::make_move_iterator(inds.begin()), std::make_move_iterator(inds.end()));
	}

	vkUtil::BufferInitInput bufferInfo = {};

	bufferInfo.logicalDevice = _vkLogicalDevice;

	bufferInfo.physicalDevice = _vkPhysicalDevice;

	_vertexBuffer = std::make_unique<VertexBuffer>(bufferInfo);

	_vertexBuffer->initalize(vertices, _debugMode);

	if (!indices.empty())
	{
		_indexBuffer = std::make_unique<IndexBuffer>(bufferInfo);
		_indexBuffer->initalize(indices, _debugMode);
	}
}


void Engine::load_scene(std::unique_ptr<SceneT>& scene)
{
	if (scene)
	{
		_scene = std::move(scene);	
	}
}


void Engine::draw_scene(vk::CommandBuffer& cmdBuffer) const
{
	if (_scene)
	{
		for (const auto& position : _scene->get_triangles_pos())
		{ 
			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)); 
			vkUtil::ObjectData objectData(vkUtil::ShaderStage::VERTEX);
			objectData.c_data._model = std::move(model);
			send_as_push_const(objectData.c_data, cmdBuffer, vkUtil::ShaderStage::VERTEX, 0);
		}
	}
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

void Engine::call_push_consts() const
{
	for (const auto& pushConst : _pushConstCalls)
	{
		pushConst();
	}

}




//template class Engine <glm::vec2, glm::vec3, nullptr_t, nullptr_t>;  
//template class Engine <glm::vec3, glm::vec3, nullptr_t, nullptr_t>;  
//template class Engine <glm::vec3, glm::vec4, nullptr_t, nullptr_t>;  
