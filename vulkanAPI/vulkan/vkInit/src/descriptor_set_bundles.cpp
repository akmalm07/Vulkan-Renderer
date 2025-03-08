#include "headers.h"
#include "vkInit\include\descriptor_set_bundles.h"


namespace vkInit
{
	DescriptorSetBindingBundle::DescriptorSetBindingBundle(vk::DescriptorType type, std::vector<vkUtil::ShaderStage> stage, uint32_t count, uint32_t binding, vk::Sampler* sampler)
		: type(type), stage(stage), count(count), binding(binding), sampler(sampler)
	{
	}


	DescriptorSetBindingBundle::DescriptorSetBindingBundle(vk::DescriptorType type, vkUtil::ShaderStage stage, uint32_t count, uint32_t binding, vk::Sampler* sampler)
		: type(type), count(count), binding(binding), sampler(sampler)
	{
		this->stage.push_back(stage);
	}

	DescriptorSetBindingBundle::DescriptorSetBindingBundle()
	{
	}

	DescriptorBuffer::DescriptorBuffer(vk::BufferUsageFlags bufferType, uint32_t maxSize, void * data)
		: bufferType(bufferType), maxSize(maxSize), data(data)
	{
	}

	DescriptorBuffer::DescriptorBuffer(const vkUtil::BufferInput& buffer, void* data)
		: bufferType(buffer.usage), maxSize(buffer.size), data(data) 
	{
	}

	DescriptorBuffer::DescriptorBuffer()
		: bufferType(0), maxSize(0), data(nullptr)
	{
	}
}