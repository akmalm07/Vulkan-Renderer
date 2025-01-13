#pragma once

#include "base_engine.h"
#include "mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "std_overloads.h"
#include "std_types.h"
#include "s_vertex.h"
#include "s_scene.h"
#include "config.h"





template <Struct T>
class SEngine : public BaseEngine
{
public:


	SEngine() : 
		BaseEngine()
	{
		indexBuffer = nullptr;

		vertexBuffer = nullptr;


	}

	SEngine(vkVertex::PosStride posStride, vkVertex::ColorStride colStride,
		vkVertex::NormalStride normStride, vkVertex::TextureStride texStride, bool debug) :
		BaseEngine(posStride, colStride, normStride, texStride, debug)
	{
		indexBuffer = nullptr;



		vertexBuffer = nullptr;
	}


	SEngine(GLFWwindow* glfwWindow,
		vkVertex::PosStride posStride, vkVertex::ColorStride colStride, vkVertex::NormalStride normStride,
		vkVertex::TextureStride texStride, bool debug) :
		BaseEngine(glfwWindow, posStride, colStride, normStride, texStride, debug)
	{

		indexBuffer = nullptr;



		vertexBuffer = nullptr;
	}


	void draw(vk::CommandBuffer& commandBuffer) override
	{
		//if (scene)
		//{
		//	for (const auto& position : scene->get_triangles())
		//	{
		//		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

		//		vkUtil::ObjectData objData = {};   

		//		objData.model = model;

		//		send_as_push_const(objData, commandBuffer, vk::ShaderStageFlagBits::eVertex, 0);
		//	}
		//}

		std::vector<vk::DeviceSize> vertOffset = { 0 };
		vertexBuffer->bind_vertex_buffer(commandBuffer, vertOffset);

		if (indexBuffer)
		{
			indexBuffer->bind_index_buffer(commandBuffer,0);
			uint32_t indexCount = cast_uint32(indexBuffer->index_count());
			commandBuffer.drawIndexed(indexCount, 1, 0, 0, 0);
		}
		else
		{
			uint32_t vertCount = cast_uint32(vertexBuffer->vertex_count()); 
			commandBuffer.draw(vertCount, 1, 0, 0);
		}

	}


	void load_scene(SScene<T>& scene)
	{
		this->scene = std::move(scene);
	}


	void load_meshes(std::vector<SMesh<T>>& meshes)
	{

		size_t indicesSize = 0, verticesSize = 0;
		
		for (const auto& mesh : meshes)
		{
			verticesSize += mesh.vertices_count();
			indicesSize += mesh.indices_size();
		}

		std::vector<float> vertices;
		vertices.reserve(verticesSize);

		std::vector<vkType::Index> indices;
		indices.reserve(indicesSize);

		for (const auto& mesh : meshes)
		{
			vertices += mesh.get_vertices();
			indices += mesh.get_indices();
		}

		vkMesh::BufferInitInput bufferInfo = {};

		bufferInfo.logicalDevice = vkLogicalDevice; 

		bufferInfo.physicalDevice = vkPhysicalDevice; 

		vertexBuffer = std::make_unique<SVertexBuffer<T>>(bufferInfo);

		vertexBuffer->initalize(vertices, debugMode);

		if (!indices.empty())
		{
			indexBuffer = std::make_unique<IndexBuffer>(bufferInfo); 
			indexBuffer->initalize(indices, debugMode);
		}
	}



	~SEngine() override
	{
		intial_clean_up();
	}

private:

	vkType::scene scene; 

	std::unique_ptr<SVertexBuffer<T>> vertexBuffer; 
	std::unique_ptr<IndexBuffer> indexBuffer;
};





//template<Struct T>
//void SEngine<T>::load_meshes(std::vector<SMesh<T>>& meshes) 


namespace vkType {

	using sengine = SEngine<VertStd<pos, col, norm, tex>>;

}