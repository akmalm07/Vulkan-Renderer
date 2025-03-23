#pragma once


#include "config.h"

#include "vkUtil\include\base_buffer.h"

#include "vkUtil\include\mesh.h"

#include "vkUtil\include\vertex.h"

#include "vkUtil\include\memory.h"




class VertexBufferT : public BufferFather  
{	
public:
	
	VertexBufferT();

	VertexBufferT(const vkUtil::BufferInitInput& input);


	void initalize(const std::vector<vkType::Vertex>& data, bool debug);

	template<size_t S>
	void initalize(const std::array<vkType::Vertex, S>& data, bool debug);


	size_t vertex_count() const;


	void bind_buffer(vk::CommandBuffer& cmdBuffer, std::vector<vk::DeviceSize>& offsets) const;



	~VertexBufferT();
	 

private:

	size_t vertexCount;
};



namespace vkType
{
	using VertexBuffer = VertexBufferT;
}

template<size_t S>
inline void VertexBufferT::initalize(const std::array<vkType::Vertex, S>& data, bool debug)
{
	createBuffer<vkType::Vertex, S>(data, bufferMemory, vk::BufferUsageFlagBits::eVertexBuffer, debug);
	vertexCount = S / vkType::Vert::count();
}
