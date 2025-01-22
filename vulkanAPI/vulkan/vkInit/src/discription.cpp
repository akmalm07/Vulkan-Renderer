#include "pch.h"

#include "vkInit\include\discription.h" 


namespace vkDiscription
{
	std::vector <vk::VertexInputAttributeDescription> vkDiscription::get_attribute_descriptions(vkVert::StrideBundle stride, uint32_t binding, bool debug)
	{
		uint32_t location = 0;

		if (stride.pos == vkVert::PosStride::NONE && debug)
		{
			std::cout << "Error:: No position was sent to the attribute description\n";
			return {};
		}

		std::vector<vk::VertexInputAttributeDescription> attributes;

		attributes.reserve(4);

		attributes.push_back(std::move(get_attribute_description(stride.pos, 0, binding, location))); 

		location++;
		uint32_t offset = vkVert::enumerate_pos_stride(stride.pos);

		if (stride.col != vkVert::ColorStride::NONE)
		{
			location++;

			attributes.push_back(std::move(get_attribute_description(stride.col, offset * sizeof(Vertex), binding, location)));

			offset += vkVert::enumerate_color_stride(stride.col); 
		}


		if (stride.norm != vkVert::NormalStride::NONE)
		{
			location++;

			attributes.push_back(std::move(get_attribute_description(stride.norm, offset * sizeof(Vertex), binding, location)));

			offset += vkVert::enumerate_normal_stride(stride.norm);

		}

		if (stride.tex != vkVert::TextureStride::NONE)
		{
			location++;

			attributes.push_back(std::move(get_attribute_description(stride.tex, offset * sizeof(Vertex), binding, location))); 

			offset += vkVert::enumerate_tex_stride(stride.tex);
		}

		return attributes;
	}



	vk::VertexInputBindingDescription vkDiscription::get_binding_description(uint32_t sizeOfEachVertex, uint32_t binding, bool perInstenceInput)
	{

		vk::VertexInputBindingDescription descriptionSet = {};

		descriptionSet.binding = binding;

		descriptionSet.stride = sizeOfEachVertex;

		descriptionSet.inputRate = (perInstenceInput ? vk::VertexInputRate::eInstance : vk::VertexInputRate::eVertex);

		return descriptionSet;

	}

}