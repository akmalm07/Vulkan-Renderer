#pragma once

#include "config.h"

#include "vkUtil\include\descriptor_set_bundles.h"


namespace tools
{

	class DescriptorSetRegistry
	{
	public:
		DescriptorSetRegistry();

		static DescriptorSetRegistry& get_instance();

		void intialize(std::vector<vkUtil::DescriptorSetInBundle> input, std::vector<uint32_t> layouts);

		std::vector<uint32_t> get_descriptor_set_layouts() const;

		std::vector<vkUtil::DescriptorSetInBundle> get_descriptor_sets() const;

		~DescriptorSetRegistry();

	private:

		std::vector<vkUtil::DescriptorSetInBundle> m_createDescriptors;
		std::vector<uint32_t> m_layouts;

	};

}