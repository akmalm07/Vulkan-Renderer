#pragma once


#include "pch.h"

#include "vkUtil\include\stride.h"


namespace vkDiscription {


	struct DiscriptorBundle
	{
		vkVert::PosStride vertStride; 
		vkVert::ColorStride colStride; 
		vkVert::NormalStride normStride; 
		vkVert::TextureStride texStride;
		bool isPerInstanceRate;
	};

	std::vector<vk::VertexInputAttributeDescription> get_attribute_descriptions(vkVert::StrideBundle stride, uint32_t binding, bool debug);

	vk::VertexInputBindingDescription get_binding_description(uint32_t sizeOfEachVertex, uint32_t binding, bool perInstenceInput);

	
	template<vkVert::Enum T> 
	vk::VertexInputAttributeDescription get_attribute_description(T stride, uint32_t offset, uint32_t binding, uint32_t location);


}


template<vkVert::Enum T>
vk::VertexInputAttributeDescription vkDiscription::get_attribute_description(T stride, uint32_t offset, 
	uint32_t binding, uint32_t location)
{
	vk::VertexInputAttributeDescription disc;

	disc.binding = binding;

	disc.location = location;

	if constexpr (std::same_as_v<T, vkVert::ColorStride>)
	{
		switch (stride)
		{

		case vkVert::ColorStride::RGB:
			disc.format = vk::Format::eR32G32B32Sfloat;
			break;

		case vkVert::ColorStride::RGBA:
			disc.format = vk::Format::eR32G32B32A32Sfloat;
			break;
		}

	}
	else
	{
		switch (stride)
		{
		case vkVert::T::STRIDE_2D:
			disc.format = vk::Format::eR32G32Sfloat;
			break;

		case vkVert::T::STRIDE_3D:
			disc.format = vk::Format::eR32G32B32Sfloat;
			break;
		}
	}
	disc.offset = offset; 

	return disc;
}