#pragma once

#include "config.h"

#include "vkUtil\include\vertex.h"
#include "tools\include\stride.h"


namespace vkDiscription 
{

	struct DescriptionOutBundleSeperate
	{
		std::array<vk::VertexInputAttributeDescription, vkType::Vert::size()> bindingAttrib; 
		std::array<vk::VertexInputBindingDescription, vkType::Vert::size()> bindingDesc; 
	}; 

	struct DescriptionOutBundle
	{
		std::array<vk::VertexInputAttributeDescription, vkType::Vert::size()> bindingAttrib; 
		vk::VertexInputBindingDescription bindingDesc; 
	}; 




	template<vkType::GLMVec T>
	vk::VertexInputAttributeDescription get_attribute_descriptions(uint32_t binding, bool debug); 
	vk::VertexInputBindingDescription get_binding_description(uint32_t binding, bool perInstenceInput, bool debug);

	DescriptionOutBundleSeperate bind_attrib_and_desc_seperate(std::array<bool, vkType::Vert::size()>instanced, bool debug);
	DescriptionOutBundle bind_attrib_and_desc(bool instanced, bool debug);

	
	std::variant<DescriptionOutBundle, DescriptionOutBundleSeperate> attrib_and_desc(bool instanced, bool debug);
	std::variant<DescriptionOutBundle, DescriptionOutBundleSeperate> attrib_and_desc(std::array<bool, vkType::Vert::size()>instanced, bool debug);
	

}


namespace 
{
	template<vkType::GLMVec T>
	vk::VertexInputAttributeDescription get_attribute_desc(uint32_t offset,
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

}


inline uint32_t& get_S_location()
{
	static uint32_t s_location = 0;
	return s_location;

}

inline uint32_t& get_S_offset()
{
	static uint32_t s_location = 0;
	return s_location;

}
	template<vkType::GLMVec T> 
	vk::VertexInputAttributeDescription vkDiscription::get_attribute_descriptions(uint32_t binding, bool debug)
	{
		uint32_t& s_location = get_S_location();
		uint32_t& s_offset = get_S_offset();

		if (s_location == 0)
		{
			if constexpr (std::same_as<T, std::nullptr_t> && debug)
			{
				std::cout << "Error:: No position was sent to the attribute description\n";
				return {};
			}

			vk::VertexInputAttributeDescription attribute = std::move(get_attribute_desc<UserInput::pos>(0, binding, s_location)); 


			s_location++;
			s_offset += vkVert::enumerate_type<UserInput::pos>();

			return attribute;
		}
		else
		{
			if constexpr (!std::same_as<T, std::nullptr_t>)
			{

				vk::VertexInputAttributeDescription attribute = std::move(get_attribute_desc<T>(s_offset * sizeof(vkType::Vertex), binding, s_location));

				s_location++;
				s_offset += UINT32(vkVert::enumerate_type<T>());

				return attribute;
			}

		}

		throw std::runtime_error("Error: Unknown type was entered for get_attribute_descriptions\n");
	}
