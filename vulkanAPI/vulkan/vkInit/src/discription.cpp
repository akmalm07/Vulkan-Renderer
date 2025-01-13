#include "vkInit\include\discription.h" 

std::vector <vk::VertexInputAttributeDescription> vkDiscription::get_attribute_description(vkVertex::PosStride vertStride,
	vkVertex::ColorStride colStride, vkVertex::NormalStride normStride,
	vkVertex::TextureStride texStride, uint32_t binding, bool debug)
{
	uint32_t location = 0;

	if (vertStride == vkVertex::PosStride::NONE && debug)
	{
		std::cout << "Error:: No position was sent to the attribute description\n";
		return {};
	}
	
	std::vector<vk::VertexInputAttributeDescription> attributes;
	
	attributes.reserve(4);

	{//empty scope
	
		vk::VertexInputAttributeDescription attribute = {};

		attribute.binding = binding;

		attribute.location = location;

		switch (vertStride) 
		{

		case vkVertex::PosStride::STRIDE_2D: 
			attribute.format = vk::Format::eR32G32Sfloat; 
			break;

		case vkVertex::PosStride::STRIDE_3D: 
			attribute.format = vk::Format::eR32G32B32Sfloat; 
			break;
		}

		attribute.offset = 0;

		attributes.push_back(std::move(attribute));

	}

	uint32_t offset = vkVertex::enumerate_pos_stride(vertStride);

	if (colStride != vkVertex::ColorStride::NONE)
	{
		location++;

		vk::VertexInputAttributeDescription attribute = {};

		attribute.binding = binding;

		attribute.location = location;

		switch (colStride)
		{

		case vkVertex::ColorStride::RGB:
			attribute.format = vk::Format::eR32G32B32Sfloat;
			break;

		case vkVertex::ColorStride::RGBA:
			attribute.format = vk::Format::eR32G32B32A32Sfloat;
			break;
		}
		attribute.offset = offset * sizeof(float);
	
		attributes.push_back(std::move(attribute));
	}

	
		

	if (normStride != vkVertex::NormalStride::NONE) 
	{
		location++;

		vk::VertexInputAttributeDescription attribute = {};

		offset += vkVertex::enumerate_normal_stride(normStride);

		attribute.binding = 0;

		attribute.location = location;

		switch (normStride)
		{

		case vkVertex::NormalStride::STRIDE_2D:
			attribute.format = vk::Format::eR32G32Sfloat;
			break;
		
		case vkVertex::NormalStride::STRIDE_3D:
			attribute.format = vk::Format::eR32G32B32Sfloat; 
			break;
		}


		attribute.offset = offset * sizeof(float);

		attributes.push_back(std::move(attribute));

	}


	if (texStride != vkVertex::TextureStride::NONE)
	{
		location++;

		vk::VertexInputAttributeDescription attribute = {};

		offset += vkVertex::enumerate_tex_stride(texStride);

		attribute.binding = 0;

		attribute.location = location;

		switch (texStride)
		{

		case vkVertex::TextureStride::STRIDE_2D:
			attribute.format = vk::Format::eR32G32Sfloat;
			break;

		case vkVertex::TextureStride::STRIDE_3D:
			attribute.format = vk::Format::eR32G32B32Sfloat;
			break;
		}


		attribute.offset = offset * sizeof(float);
	
		attributes.push_back(std::move(attribute)); 
	}
	


	return attributes;
}

vk::VertexInputBindingDescription vkDiscription::get_binding_description(uint32_t sizeOfEachVertex, uint32_t binding, bool perInstenceInput)
{

	vk::VertexInputBindingDescription descriptionSet = {};

	descriptionSet.binding = binding;
	
	descriptionSet.stride = sizeOfEachVertex;
	
	descriptionSet.inputRate = (perInstenceInput ? vk::VertexInputRate::eInstance : vk::VertexInputRate::eVertex );

	return descriptionSet;

}
