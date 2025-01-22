#pragma once


#include "config.h"

#include "vkUtil\include\base_buffer.h"

#include "vkUtil\include\mesh.h"

#include "vkUtil\include\vertex.h"

#include "vkUtil\include\memory.h"




class VertexBufferT : private BufferFather  
{	
public:
	
	VertexBufferT();

	VertexBufferT(const vkUtil::BufferInitInput& input);


	void initalize(std::vector<float>& data, bool debug);


	size_t vertex_count() const;


	void bind_buffer(vk::CommandBuffer& cmdBuffer, std::vector<vk::DeviceSize>& offsets) const;



	~VertexBufferT();
	 

private:

	size_t vertexCount;
};




using VertexBuffer = VertexBufferT; 
