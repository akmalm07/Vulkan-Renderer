#include "headers.h"

#include "vkUtil\include\IndexBuffer.h"
#include "vkUtil\include\memory.h"


IndexBufferT::IndexBufferT() : BufferFather() 
{}

IndexBufferT::IndexBufferT(const vkUtil::BufferInitInput& bufferInfo)
	: BufferFather(bufferInfo), indexCount(0)
{}


void IndexBufferT::initalize(const std::vector<vkType::Index>& data, bool debug)
{
	createBuffer<vkType::Index>(data, bufferMemory, vk::BufferUsageFlagBits::eIndexBuffer, debug);
	indexCount = data.size();
}


void IndexBufferT::bind_buffer(vk::CommandBuffer& cmdBuffer, size_t offsets) const 
{
	cmdBuffer.bindIndexBuffer(buffer, offsets, vkType::convert_type_to_vk_index_enum<INDEX_TYPE>()); 
}



size_t IndexBufferT::index_count() const
{
	return indexCount;
}



IndexBufferT::~IndexBufferT() = default;