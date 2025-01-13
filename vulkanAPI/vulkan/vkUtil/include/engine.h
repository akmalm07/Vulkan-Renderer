#pragma once

#include "pch.h"

#include "vkUtil\include\base_engine.h"
#include "vkUtil\include\mesh.h"
#include "vkUtil\include\VertexBuffer.h"
#include "vkUtil\include\IndexBuffer.h"
#include "vkUtil\include\scene.h"




namespace vkInit {

	struct SwapChainFrame; 

}

namespace vkUtil {
	struct SwapChainFrame;
}




template <GLMVec POS, GLMVec COL, GLMVec NORM, GLMVec TEX>
class Engine : public BaseEngine  
{
public:

	Engine() : 
		BaseEngine()
	{
		indexBuffer = nullptr;
		


		vertexBuffer = nullptr;
	}

	Engine(vkVertex::PosStride posStride, vkVertex::ColorStride colStride,
		vkVertex::NormalStride normStride, vkVertex::TextureStride texStride, bool debug) : 
		BaseEngine(posStride, colStride, normStride, texStride, debug)
	{
		indexBuffer = nullptr;



		vertexBuffer = nullptr;
	}


	Engine(GLFWwindow * glfwWindow,
		vkVertex::PosStride posStride, vkVertex::ColorStride colStride, vkVertex::NormalStride normStride,
		vkVertex::TextureStride texStride, bool debug) :
		BaseEngine(glfwWindow, posStride, colStride, normStride, texStride, debug)
	{

		indexBuffer = nullptr;



		vertexBuffer = nullptr;
	}
	

	void load_meshes(std::vector<Mesh<POS, COL, NORM, TEX>>& meshes)
	{
		size_t indicesSize = 0, verticesSize = 0;

		for (const auto& mesh : meshes)
		{
			verticesSize += mesh.get_vertices_count(); 
			indicesSize += mesh.indices_size(); 
		}

		std::vector<float> vertices;
		vertices.reserve(verticesSize); 

		std::vector<vkType::Index> indices; 
		indices.reserve(indicesSize);

		for (const auto& mesh : meshes)
		{
			vertices += mesh.get_vertices_raw();
			std::cout << " RAW \n";
			for (const auto& vert : vertices)
			{
				std::cout << " " << vert << " ";
			}
			std::cout << "\n";
			std::cout << "SIZE: " << vertices.size() << "\n";

			indices += mesh.get_indices();
		}

		vkMesh::BufferInitInput bufferInfo = {};

		bufferInfo.logicalDevice = vkLogicalDevice;

		bufferInfo.physicalDevice = vkPhysicalDevice;

		vertexBuffer = std::make_unique<VertexBuffer<POS, COL, NORM, TEX>>(bufferInfo);

		vertexBuffer->initalize(vertices, debugMode); 

		if (!indices.empty())
		{
			indexBuffer = std::make_unique<IndexBuffer>(bufferInfo);
			indexBuffer->initalize(indices, debugMode); 
		}
	}



	void load_scene(std::unique_ptr <Scene<POS, COL, NORM, TEX>>& scene)
	{
		if (scene)
		{
			this->scene = std::move(scene);
		}
	}


	void draw(vk::CommandBuffer& commandBuffer) override
	{
		if (scene)
		{
			for (const auto& position : scene->get_triangles()) 
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), position); 
				vkUtil::ObjectData objectData; 
				objectData.model = model; 
			}
		}

	/*	if (vertexBuffer)
		{
			std::vector<vk::DeviceSize> vertOffset = { 0 };
			vertexBuffer->bind_vertex_buffer(commandBuffer, vertOffset);
		}

		if (indexBuffer)
		{
			indexBuffer->bind_index_buffer(commandBuffer, 0);

			uint32_t indexCount = cast_uint32(indexBuffer->index_count());
			commandBuffer.drawIndexed(indexCount, 1, 0, 0, 0);
		}
		else
		{
			uint32_t vertCount = cast_uint32(vertexBuffer->vertex_count());   
			commandBuffer.draw(vertCount, 1, 0, 0);
		}*/

	
	}


	~Engine() override
	{
		intial_clean_up(); 

	}


private:

	std::unique_ptr <vkType::scene> scene; 

	std::unique_ptr<VertexBuffer<POS, COL, NORM, TEX>> vertexBuffer;   
	std::unique_ptr<IndexBuffer> indexBuffer; 


};



namespace vkType 
{

	using engine = Engine<pos, col, norm, tex>; 
}
