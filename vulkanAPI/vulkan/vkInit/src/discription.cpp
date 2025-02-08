#include "pch.h"

#include "vkInit\include\discription.h" 
#include "vkUtil\include\vertex.h" 




namespace vkDiscription
{	

	vk::VertexInputBindingDescription get_binding_description(uint32_t binding, bool perInstenceInput, bool debug)
	{
		if (debug)
		{
			std::cout << "Creating Binding " << binding << " Description for VertexBuffer... \n";
		}
		vk::VertexInputBindingDescription descriptionSet = {};

		descriptionSet.binding = binding;

		descriptionSet.stride = vkType::Vert::count() * sizeof(vkType::Vertex);
		 
		descriptionSet.inputRate = (perInstenceInput ? vk::VertexInputRate::eInstance : vk::VertexInputRate::eVertex);

		return descriptionSet;

	}



	DescriptionOutBundleSeperate bind_attrib_and_desc_seperate(std::array<bool, vkType::Vert::size()> instanced, bool debug)
	{
		uint32_t binding = 0;

		DescriptionOutBundleSeperate out;

		if constexpr (!std::same_as<UserInput::pos, std::nullptr_t>) 
		{
			if (debug)
			{
				std::cout << "Creating Attribute Descriptions position for binding " << binding << " ... \n";
				std::cout << "Creating Binding Descriptions for binding " << binding << " ... \n";
			}

			out.bindingAttrib[binding] = get_attribute_descriptions<UserInput::pos>(binding, debug);
			out.bindingDesc[binding] = get_binding_description(binding, instanced[binding], debug);
			binding++; 
		}


		
		if constexpr (!std::same_as<UserInput::col, std::nullptr_t>) 
		{
			if (debug)
			{
				std::cout << "Creating Attribute Descriptions color for binding " << binding << " ... \n";
				std::cout << "Creating Binding Descriptions for binding " << binding << " ... \n";
			}


			out.bindingAttrib[binding] = get_attribute_descriptions<UserInput::col>(binding, debug); 
			out.bindingDesc[binding] = get_binding_description(binding, instanced[binding], debug); 
			binding++; 
		}



		if constexpr (!std::same_as<UserInput::norm, std::nullptr_t>)
		{
			if (debug)
			{
				std::cout << "Creating Attribute Descriptions normal for binding " << binding << " ... \n";
				std::cout << "Creating Binding Descriptions for binding " << binding << " ... \n";
			}


			out.bindingAttrib[binding] = get_attribute_descriptions<UserInput::norm>(binding, debug); 
			out.bindingDesc[binding] = get_binding_description(binding, instanced[binding], debug);
			binding++;  
		}



		if constexpr (!std::same_as<UserInput::tex, std::nullptr_t>) 
		{
			if (debug)
			{
				std::cout << "Creating Attribute Descriptions texture for binding " << binding << " ... \n";
				std::cout << "Creating Binding Descriptions for binding " << binding << " ... \n"; 
			}

			out.bindingAttrib[binding] = get_attribute_descriptions<UserInput::tex>(binding, debug);
			out.bindingDesc[binding] = get_binding_description(binding, instanced[binding], debug);
			binding++; 
		}


		return out;
	}



	DescriptionOutBundle bind_attrib_and_desc(bool instanced, bool debug) 
	{
		uint32_t index = 0;

		DescriptionOutBundle out;


		if constexpr (!std::same_as<UserInput::pos, std::nullptr_t>) 
		{
			if (debug)
			{
				std::cout << "Creating Attribute Descriptions position for binding " << 0 << " ... \n";
			}

			out.bindingAttrib[index] = get_attribute_descriptions<UserInput::pos>(0, debug);
			index++;
		}


		if constexpr (!std::same_as<UserInput::col, std::nullptr_t>) 
		{
			if (debug)
			{
				std::cout << "Creating Attribute Descriptions color for binding " << 0 << " ... \n";
			}
			out.bindingAttrib[index] = get_attribute_descriptions<UserInput::col>(0, debug);
			index++;
		}


		if constexpr (!std::same_as<UserInput::norm, std::nullptr_t>) 
		{
			if (debug) 
			{
				std::cout << "Creating Attribute Descriptions normal for binding " << 0 << " ... \n";
			}
			out.bindingAttrib[index] = get_attribute_descriptions<UserInput::norm>(0, debug);
			index++;
		}



		if constexpr (!std::same_as<UserInput::tex, std::nullptr_t>) 
		{
			if (debug)
			{
				std::cout << "Creating Attribute Descriptions texture for binding " << 0 << " ... \n";
			}
			out.bindingAttrib[index] = get_attribute_descriptions<UserInput::tex>(0, debug);
			index++;
		}

		out.bindingDesc = get_binding_description(0, instanced, debug);


		return out;
	}

	std::variant<DescriptionOutBundle, DescriptionOutBundleSeperate> attrib_and_desc(bool instanced, bool debug)
	{
		return bind_attrib_and_desc(instanced, debug);
	}

	std::variant<DescriptionOutBundle, DescriptionOutBundleSeperate> attrib_and_desc(std::array<bool, vkType::Vert::size()> instanced, bool debug)
	{
		return bind_attrib_and_desc_seperate(instanced, debug); 
	}





} // vkDiscription