#include "pch.h"

#include "VertexBuffer.h"



VertexBufferT::VertexBufferT() : BufferFather()
{}


VertexBufferT::VertexBufferT(const vkUtil::BufferInitInput& input) :
	BufferFather(input), vertexCount(0)
{
}


void VertexBufferT::initalize(std::vector<float>& data, bool debug)
{
	createBuffer<float>(data, bufferMemory, vk::BufferUsageFlagBits::eVertexBuffer, vertexCount, debug);
}


size_t VertexBufferT::vertex_count() const
{
	return vertexCount;
}



void VertexBufferT::bind_buffer(vk::CommandBuffer& cmdBuffer, std::vector<vk::DeviceSize>& offsets) const
{
	std::vector<vk::Buffer> buffers = { buffer };
	cmdBuffer.bindVertexBuffers(0, buffers, offsets);
}



VertexBufferT::~VertexBufferT() = default;