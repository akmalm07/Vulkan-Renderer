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

		DescriptorBuffer();
		DescriptorBuffer(vk::BufferUsageFlags bufferType, uint32_t maxSize);
	public:
		virtual void* get_data_ptr() = 0;
	};

	template<class T>
	struct DescriptorBufferData : public DescriptorBuffer
	{
	public:
		T data;

		DescriptorBufferData(vk::BufferUsageFlags bufferType, uint32_t maxSize, T data) : data(data), DescriptorBuffer(bufferType, maxSize ) {}
		DescriptorBufferData(const DescriptorBuffer& buffer) : DescriptorBuffer(buffer.bufferType, buffer.maxSize ) {}
		DescriptorBufferData(const vkUtil::BufferInput& buffer, T data) : DescriptorBuffer(buffer.usage, buffer.size ), data(data) {}
		DescriptorBufferData(const DescriptorBuffer& buffer, T data) : DescriptorBuffer(buffer.bufferType, buffer.maxSize ), data(data) {}

	public:
		virtual void* get_data_ptr() override;
	};


	template<class T>
	inline void* DescriptorBufferData<T>::get_data_ptr() 
	{
		return &data;
	}

}