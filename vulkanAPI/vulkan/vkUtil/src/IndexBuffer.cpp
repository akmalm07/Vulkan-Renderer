#include "IndexBuffer.h"
#include "memory.h"


IndexBuffer::IndexBuffer(vkMesh::BufferInitInput& bufferInfo)
	: device(bufferInfo.logicalDevice), physicalDevice(bufferInfo.physicalDevice)
{
	indexCount = 0;
}


void IndexBuffer::initalize(std::vector<vkType::Index>& data, bool debug)
{
	if (debug)
	{
		std::cout << "Initalizing the index buffer...\n";
	}

	if (debug && data.empty()) 
	{
		std::cout << "Error! The vector inserted into the initialize function of Index Buffer is empty\n";
	}


	vkUtil::BufferInput input = {};
	input.device = physicalDevice;
	input.logicalDevice = device;
	input.size = data.size() * sizeof(data[0]);
	input.usage = vk::BufferUsageFlagBits::eIndexBuffer; 


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

	indexCount = data.size();
}


vk::Buffer IndexBuffer::get_index_buffer() const 
{
	return buffer;
}



void IndexBuffer::bind_index_buffer(vk::CommandBuffer& cmdBuffer, size_t offsets) const
{
	cmdBuffer.bindIndexBuffer(buffer, offsets, vkUtil::convert_type_to_vk_index_enum<INDEX_TYPE>());
}



size_t IndexBuffer::index_count() const
{
	return indexCount;
}



void IndexBuffer::clean_index_buffer() 
{

	indexCount = 0;

	if (buffer)
	{
		device.destroyBuffer(buffer);
		buffer = nullptr;
	}
	if (bufferMemory)
	{
		device.freeMemory(bufferMemory);
		bufferMemory = nullptr;
	}
	device = nullptr;

}



IndexBuffer::~IndexBuffer()
{
	clean_index_buffer();
}