#pragma once

#include "config.h"

#include "vkUtil\include\base_buffer.h"

#include "vkUtil\include\mesh.h"

#include "vkUtil\include\memory.h"




class IndexBufferT : public BufferFather
{
public: 

	IndexBufferT();
	
	IndexBufferT(const vkUtil::BufferInitInput& bufferInfo);
	
	void initalize(const std::vector<vkType::Index>& data, bool debug);

	void bind_buffer(vk::CommandBuffer& cmdBuffer, size_t offsets) const;

	size_t index_count() const;

	~IndexBufferT();


private:

	size_t indexCount;
};


using IndexBuffer = IndexBufferT; 
