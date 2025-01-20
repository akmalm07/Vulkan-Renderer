#pragma once


#include "config.h"

#include "vkUtil\include\base_buffer.h"

#include "vkUtil\include\mesh.h"

#include "vkUtil\include\vertex.h"

#include "vkUtil\include\memory.h"




class VertexBufferT : private BufferFather  
{	
public:
	
	 VertexBufferT() : BufferFather()
	{}


	VertexBufferT(const vkMesh::BufferInitInput& input) : 
		BufferFather(input), vertexCount(0)
	{
	}



	void initalize(std::vector<float>& data, bool debug)
	{
		createBuffer<float>(data, bufferMemory, vk::BufferUsageFlagBits::eVertexBuffer, vertexCount, debug); 
	}


	size_t vertex_count() const
	{
		return vertexCount;
	}



	void bind_buffer(vk::CommandBuffer& cmdBuffer, std::vector<vk::DeviceSize>& offsets) const
	{
		std::vector<vk::Buffer> buffers = { buffer };
		cmdBuffer.bindVertexBuffers(0, buffers, offsets);
	}



	~VertexBufferT() = default;
	 

private:

	size_t vertexCount;
};




using VertexBuffer = VertexBufferT; 
