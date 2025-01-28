#pragma once

#include "config.h"

#include "vkUtil\include\stride.h"


namespace vkDiscription {

	AllInOneVertBuffer get_attribute_descriptions_one_buffer(uint32_t binding, bool debug);

	template<vkType::GLMVec T>
	OncePerVertBuffer get_attribute_descriptions_seperate_buffers(uint32_t binding, bool debug);

	vk::VertexInputBindingDescription get_binding_description(uint32_t binding, bool perInstenceInput, bool debug);

	template<vkType::GLMVec T>
	vk::VertexInputAttributeDescription get_attribute_desc(uint32_t offset, uint32_t binding, uint32_t location);


}

	template<vkType::GLMVec T>
	vk::VertexInputAttributeDescription vkDiscription::get_attribute_desc(uint32_t offset,
		uint32_t binding, uint32_t location)
	{
		vk::VertexInputAttributeDescription disc;

		disc.binding = binding;

		disc.location = location;

		switch (vkVert::enumify_type<T>())
		{


		case vkVert::Stride::STRIDE_2D: 
			disc.format = vk::Format::eR32G32Sfloat; 
			break;

		case vkVert::Stride::STRIDE_3D:
			disc.format = vk::Format::eR32G32B32Sfloat; 
			break;

		case vkVert::Stride::STRIDE_4D:
			disc.format = vk::Format::eR32G32B32A32Sfloat; 
			break;
			

		}

		disc.offset = offset; 

		return disc;
	}



	template<vkType::GLMVec T>
	OncePerVertBuffer vkDiscription::get_attribute_descriptions_seperate_buffers(uint32_t binding, bool debug)  
	{
		static uint32_t location = 0;
		static uint32_t offset = 0;

		if (location == 0)
		{
			if constexpr (std::same_as<T, std::nullptr_t> && debug)
			{
				std::cout << "Error:: No position was sent to the attribute description\n";
				return {};
			}

			vk::VertexInputAttributeDescription attribute = get_attribute_desc<UserInput::pos>(0, binding, location); 
			 
			location++;
			offset += vkVert::enumerate_type<UserInput::pos>(); 

			return attribute;
		}
		else
		{
			if constexpr (!std::same_as<T, std::nullptr_t>)
			{
				location++;

				vk::VertexInputAttributeDescription attribute = get_attribute_desc<T>(offset * sizeof(vkType::Vertex), binding, location));

				offset += UINT32(vkVert::enumerate_col_type<T>()); 

				return attribute;
			}

		}

		throw std::runtime_error("Error: Unknown type was entered for get_attribute_descriptions_seperate_buffers\n");  
		return nullptr;
	}