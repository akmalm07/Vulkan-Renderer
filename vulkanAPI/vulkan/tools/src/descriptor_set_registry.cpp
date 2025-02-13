#include "pch.h"
#include "tools\include\descriptor_set_registry.h"


namespace tools
{

	DescriptorSetRegistry::DescriptorSetRegistry() = default;

	DescriptorSetRegistry& DescriptorSetRegistry::get_instance()
	{
		static DescriptorSetRegistry instance;
		return instance;
	}

	void DescriptorSetRegistry::intialize(std::vector<vkUtil::DescriptorSetInBundle> input, std::vector<uint32_t> layouts)
	{
		m_createDescriptors = std::move(input);
		m_layouts = std::move(layouts);
	}


	std::vector<vkUtil::DescriptorSetInBundle> DescriptorSetRegistry::get_descriptor_sets() const
	{
		return m_createDescriptors;
	}

	std::vector<uint32_t> DescriptorSetRegistry::get_descriptor_set_layouts() const
	{
		return m_layouts;
	}

	DescriptorSetRegistry::~DescriptorSetRegistry() = default;
}