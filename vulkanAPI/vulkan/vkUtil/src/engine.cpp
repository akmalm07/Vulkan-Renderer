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


void Engine::load_meshes(std::vector<Mesh>& meshes) const
{
	size_t indicesSize = 0, verticesSize = 0;

	for (const auto& mesh : meshes)
	{
		verticesSize += mesh.get_vert_count();
		indicesSize += mesh.ind_size();
	}

	std::vector<float> vertices;
	vertices.reserve(verticesSize);

	std::vector<vkType::Index> indices;
	indices.reserve(indicesSize);

	for (const auto& mesh : meshes)
	{
		vertices.insert(vertices.end(), mesh.get_vertices().begin(), mesh.get_vertices().end());

		/*		for (const auto& vert : vertices)
				{
					std::cout << " " << vert << " ";
				}
				std::cout << "\n";
				std::cout << "SIZE: " << vertices.size() << "\n";
				*/

		indices.insert(indices.end(), mesh.get_indices().begin(), mesh.get_indices().end());
	}

	vkMesh::BufferInitInput bufferInfo = {};

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




void Engine::load_scene(std::unique_ptr<Scene>& scene)
{
	if (scene)
	{
		_scene = std::move(scene);
	}
}


void Engine::draw(vk::CommandBuffer& commandBuffer) const
{
	if (_scene)
	{
		for (const auto& position : _scene->get_triangles())
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
			vkUtil::ObjectData objectData;
			objectData.model = model;
		}
	}

	/*	if (_vertexBuffer)
		{
			std::vector<vk::DeviceSize> vertOffset = { 0 };
			_vertexBuffer->bind_vertex_buffer(commandBuffer, vertOffset);
		}

		if (_indexBuffer)
		{
			_indexBuffer->bind_index_buffer(commandBuffer, 0);

			uint32_t indexCount = cast_uint32(_indexBuffer->index_count());
			commandBuffer.drawIndexed(indexCount, 1, 0, 0, 0);
		}
		else
		{
			uint32_t vertCount = cast_uint32(_vertexBuffer->vertex_count());
			commandBuffer.draw(vertCount, 1, 0, 0);
		}*/


}




//template class Engine <glm::vec2, glm::vec3, nullptr_t, nullptr_t>;  
//template class Engine <glm::vec3, glm::vec3, nullptr_t, nullptr_t>;  
//template class Engine <glm::vec3, glm::vec4, nullptr_t, nullptr_t>;  
