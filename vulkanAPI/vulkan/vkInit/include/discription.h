#pragma once


#include "pch.h"

#include "vkType\include\stride.h"


namespace vkDiscription {


	struct DiscriptorBundle
	{
		vkVertex::PosStride vertStride; 
		vkVertex::ColorStride colStride; 
		vkVertex::NormalStride normStride; 
		vkVertex::TextureStride texStride;
		bool isPerInstanceRate;
	};

	std::vector<vk::VertexInputAttributeDescription> get_attribute_description(vkVertex::PosStride vertStride, 
		vkVertex::ColorStride colStride, vkVertex::NormalStride normStride, 
		vkVertex::TextureStride texStride, uint32_t binding, bool debug);


	vk::VertexInputBindingDescription get_binding_description(uint32_t sizeOfEachVertex, uint32_t binding, bool perInstenceInput);
}
