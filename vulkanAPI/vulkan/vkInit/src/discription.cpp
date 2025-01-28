#include "pch.h"

#include "vkInit\include\discription.h" 
#include "vkUtil\include\vertex.h" 


namespace vkDiscription
{
	

	UserInput::AttributeDescription get_attribute_descriptions_one_buffer(uint32_t binding, bool debug) 
	{
		uint32_t location = 0;

		if constexpr (std::same_as<UserInput::pos, std::nullptr_t> && debug) 
		{
			std::cout << "Error:: No position was sent to the attribute description\n";
			return {};
		}

		std::vector<vk::VertexInputAttributeDescription> attributes;

		attributes.reserve(4);

		if (debug)
		{
			std::cout << "Creating Attribute Descriptions for binding "<< binding << " ... \n";
			std::cout << "\tCreating Attribute Description of position for VertexBuffer... \n";
		}

		attributes.emplace_back(get_attribute_desc<UserInput::pos>(0, binding, location));  

		location++;
		uint32_t offset = vkVert::enumerate_type<UserInput::pos>();

		if constexpr (!std::same_as<UserInput::col, std::nullptr_t>)
		{
			if (debug)
			{
				std::cout << "\tCreating Attribute Description of color for VertexBuffer... \n";
			}

			location++;

			attributes.emplace_back(get_attribute_desc<UserInput::col>(offset * sizeof(vkType::Vertex), binding, location));

			offset += UINT32(vkVert::enumerate_type<UserInput::col>());
		}

		if constexpr (!std::same_as<UserInput::norm, std::nullptr_t>) 
		{
			if (debug)
			{
				std::cout << "\tCreating Attribute Description of normal for VertexBuffer... \n";
			}

			location++;

			attributes.emplace_back(get_attribute_desc<UserInput::norm>(offset * sizeof(vkType::Vertex), binding, location));

			offset += UINT32(vkVert::enumerate_type<UserInput::norm>());

		}

		if constexpr (!std::same_as<UserInput::tex, std::nullptr_t>) 
		{
			if (debug)
			{
				std::cout << "\tCreating Attribute Description of texture for VertexBuffer... \n";
			}

			location++;

			attributes.emplace_back(get_attribute_desc<UserInput::tex>(offset * sizeof(vkType::Vertex), binding, location)); 

			offset += UINT32(vkVert::enumerate_type<UserInput::tex>());
		}

		return attributes;
	}

	vk::VertexInputBindingDescription get_binding_description(uint32_t binding, bool perInstenceInput, bool debug)
	{
		if (debug)
		{
			std::cout << "Creating Binding " << binding << " Description for VertexBuffer... \n";
		}
		vk::VertexInputBindingDescription descriptionSet = {};

		descriptionSet.binding = binding;

		descriptionSet.stride = vkType::Vert::size();

		descriptionSet.inputRate = (perInstenceInput ? vk::VertexInputRate::eInstance : vk::VertexInputRate::eVertex);

		return descriptionSet;

	}

}