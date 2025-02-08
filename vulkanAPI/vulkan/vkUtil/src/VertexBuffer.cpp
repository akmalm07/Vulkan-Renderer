#include "pch.h"

#include "vkUtil\include\VertexBuffer.h"

#include "vkUtil\include\vertex.h"


VertexBufferT::VertexBufferT() : BufferFather()
{}


VertexBufferT::VertexBufferT(const vkUtil::BufferInitInput& input) :
	BufferFather(input), vertexCount(0)
{
}


void VertexBufferT::initalize(const std::vector<vkType::Vertex>& data, bool debug)
{
	createBuffer<vkType::Vertex>(data, bufferMemory, vk::BufferUsageFlagBits::eVertexBuffer, debug);
	vertexCount = data.size() / vkType::Vert::count();
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