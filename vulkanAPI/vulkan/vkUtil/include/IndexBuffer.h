#pragma once

#include "config.h"

#include "vkUtil\include\base_buffer.h"

#include "vkUtil\include\mesh.h"

#include "vkUtil\include\memory.h"




class IndexBufferT : private BufferFather
{
public: 

	IndexBufferT();
	
	IndexBufferT(const vkMesh::BufferInitInput& bufferInfo);
	
	void initalize(std::vector<vkType::Index>& data, bool debug);

	void bind_buffer(vk::CommandBuffer& cmdBuffer, size_t offsets) const;

	size_t index_count() const;

	~IndexBufferT();


private:

	size_t indexCount;
};


using IndexBuffer = IndexBufferT; 
