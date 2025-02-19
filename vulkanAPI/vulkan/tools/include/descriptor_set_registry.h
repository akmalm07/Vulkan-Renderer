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

		void intialize(std::vector<vkInit::DescriptorSetBindings>& input, std::vector<vkInit::DescriptorSetBindings>& layouts, std::vector<vkUtil::BufferInput>& buffers);

		std::vector<vkInit::DescriptorSetBindings> get_descriptor_set_layouts() const;

		std::vector<vkInit::DescriptorSetBindings> get_descriptor_sets() const;

		std::vector<vkUtil::BufferInput> get_descriptor_buffers() const;

		~DescriptorSetRegistry();

	private:

		DescriptorSetRegistry();
		std::vector<vkInit::DescriptorSetBindings> m_createDescriptors;
		std::vector<vkInit::DescriptorSetBindings> m_layouts;
		std::vector<vkUtil::BufferInput> m_buffers;
	};

}