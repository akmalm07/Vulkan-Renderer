#pragma once

#include "config.h"

#include "buffers.h"

#include "mesh.h"

#include "index.h"

#include "memory.h"




class IndexBuffer : public vkUtil::Buffer 
{
public:
	IndexBuffer();

	IndexBuffer(vkMesh::BufferInitInput& bufferInfo);
	
	void initalize(std::vector<vkType::Index>& data, bool debug);

	vk::Buffer get_index_buffer() const;

	void bind_index_buffer(vk::CommandBuffer& cmdBuffer, size_t offsets) const;

	size_t index_count() const;

	void clean_index_buffer();

	~IndexBuffer();


private:

	vk::Device device;
	vk::PhysicalDevice physicalDevice;

	size_t indexCount;
};

