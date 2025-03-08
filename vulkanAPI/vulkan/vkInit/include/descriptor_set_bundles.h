#pragma once


#include "config.h"

#include "vkUtil\include\shader_bundles.h"
#include "vkUtil\include\buffers.h"


namespace vkInit
{

	struct DescriptorSetBindingBundle
	{
		vk::DescriptorType type;
		std::vector<vkUtil::ShaderStage> stage;
		uint32_t count;  // number of descriptors
		uint32_t binding;
		vk::Sampler* sampler = nullptr;

		DescriptorSetBindingBundle();

		DescriptorSetBindingBundle(vk::DescriptorType type, std::vector<vkUtil::ShaderStage> stage, uint32_t count, uint32_t binding, vk::Sampler* sampler = nullptr);

		DescriptorSetBindingBundle(vk::DescriptorType type, vkUtil::ShaderStage stage, uint32_t count, uint32_t binding, vk::Sampler* sampler = nullptr);
	};

	using DescriptorSetBindings = std::vector<DescriptorSetBindingBundle>;


	struct DescriptorSetOutBundle
	{
		std::vector<vk::DescriptorSet> descriptorSets;
		std::vector<vk::DescriptorSetLayout> descriptorSetLayouts;
		std::vector<vkUtil::Buffer> descriptorSetBuffers;
		vk::DescriptorPool pool;
	};


	struct DescriptorBuffer
	{
	public:
		vk::BufferUsageFlags bufferType;
		uint32_t maxSize;
		void* data = nullptr;


		DescriptorBuffer();
		DescriptorBuffer(vk::BufferUsageFlags bufferType, uint32_t maxSize, void* data);
		DescriptorBuffer(const vkUtil::BufferInput& buffer, void* data);
	};

}