#include "pch.h"
#include "tools\include\descriptor_set_registry.h"
#include "vkInit\include\descriptor_set_bundles.h"


namespace tools
{

	DescriptorSetRegistry::DescriptorSetRegistry() = default;

	DescriptorSetRegistry& DescriptorSetRegistry::get_instance()
	{
		static DescriptorSetRegistry instance;
		return instance;
	}

	void DescriptorSetRegistry::intialize(std::vector<vkInit::DescriptorSetBindings>& input, std::vector<vkInit::DescriptorSetBindings>& layouts, std::vector<vkUtil::BufferInput>& buffers)
	{
		m_createDescriptors = std::move(input);
		m_layouts = std::move(layouts);
		m_buffers = std::move(buffers);
	}


	std::vector<vkInit::DescriptorSetBindings> DescriptorSetRegistry::get_descriptor_sets() const
	{
		return m_createDescriptors;
	}
	
	std::vector<vkUtil::BufferInput> DescriptorSetRegistry::get_descriptor_buffers() const
	{
		return m_buffers;
	}

	std::vector<vkInit::DescriptorSetBindings> DescriptorSetRegistry::get_descriptor_set_layouts() const
	{
		return m_layouts;
	}

	DescriptorSetRegistry::~DescriptorSetRegistry() = default;
}