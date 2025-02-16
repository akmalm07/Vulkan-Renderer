#pragma once

#include "config.h"

#include "vkInit\include\descriptor_set_bundles.h"
#include "vkUtil\include\shader_bundles.h"


namespace tools
{

	class DescriptorSetRegistry
	{
	public:

		static DescriptorSetRegistry& get_instance();

		void intialize(std::vector<std::vector<vkInit::DescriptorSetBindingBundle>> input, std::vector< std::vector<vkInit::DescriptorSetBindingBundle>> layouts);

		std::vector< std::vector<vkInit::DescriptorSetBindingBundle>> get_descriptor_set_layouts() const;

		std::vector<std::vector<vkInit::DescriptorSetBindingBundle>> get_descriptor_sets() const;

		~DescriptorSetRegistry();

	private:

		DescriptorSetRegistry();
		std::vector<std::vector<vkInit::DescriptorSetBindingBundle>> m_createDescriptors;
		std::vector<std::vector<vkInit::DescriptorSetBindingBundle>> m_layouts;

	};

}