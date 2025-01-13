#pragma once


#include "config.h"

#include "buffers.h"

#include "mesh.h"

#include "vertex.h"

#include "memory.h"




template <GLMVec POS, GLMVec COL, GLMVec NORM, GLMVec TEX> 
class VertexBuffer : public vkUtil::Buffer  
{
public:
	
	VertexBuffer();


	VertexBuffer(vkMesh::BufferInitInput& input)
		: device(input.logicalDevice), physicalDevice(input.physicalDevice)
	{
		vertexCount = 0;
	}



	void initalize(std::vector<float>& data, bool debug)
	{
		if (debug)
		{
			std::cout << "Initalizing the vertex buffer...\n";

			if (data.empty())
			{
				std::cout << "Error! The vector inserted into the initialize function of Vertex Buffer is empty\n";
			}	
		}

		vkUtil::BufferInput input = {}; 
		input.device = physicalDevice;    
		input.logicalDevice = device; 
		input.size = data.size() * sizeof(float);
		input.usage = vk::BufferUsageFlagBits::eVertexBuffer;

		buffer = vkUtil::create_buffer(input, debug);
		if (debug)
		{
			std::cout << "Creating the vertex buffer...\n";
			if (!buffer)
			{
				std::cout << "Error: Failed to create vertex buffer!\n";
			}
		}


		bufferMemory = vkUtil::alloc_buffer_memory(buffer, input);
		if (debug)
		{
			std::cout << "Allocating the vertex buffer...\n";

			if (!bufferMemory)
			{
				std::cout << "Error: Failed to allocate vertex buffer memory!\n";
			}
		}


		void* memLocation = device.mapMemory(bufferMemory, 0, input.size);

		if (!memLocation)
		{
			std::cout << "Error: Failed to map memory!\n";
		}

		memcpy(memLocation, data.data(), input.size);

		device.unmapMemory(bufferMemory);

		vertexCount = data.size();
	}


	vk::Buffer get_vertex_buffer() const
	{
		return buffer;
	}


	size_t vertex_count() const
	{
		return vertexCount;
	}



	void bind_vertex_buffer(vk::CommandBuffer& cmdBuffer, std::vector<vk::DeviceSize>& offsets) const
	{
		std::vector<vk::Buffer> buffers = { buffer };
		cmdBuffer.bindVertexBuffers(0, buffers, offsets);
	}


	void clean_vertex_buffer()
	{
		vertexCount = 0;

		if (bufferMemory)
		{
			device.freeMemory(bufferMemory);
			bufferMemory = nullptr;
		}
		if (buffer)
		{
			device.destroyBuffer(buffer); 
			buffer = nullptr;
		}

	}




	~VertexBuffer()
	{
		clean_vertex_buffer(); 
	}
	 

private:

	size_t vertexCount;

	vk::Device device;
	vk::PhysicalDevice physicalDevice;
};



template <typename Pos, typename Col>
using SVertexBuffer2D = VertexBuffer <Pos, Col, std::nullptr_t, std::nullptr_t>;



template <Struct Parameter>
using SVertexBuffer = VertexBuffer	<typename Parameter::Position, typename Parameter::Color, 
	typename Parameter::Normal, typename Parameter::Texture>;