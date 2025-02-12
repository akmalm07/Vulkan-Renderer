#include "pch.h"
#include "vkUtil\include\descriptor_set.h"


namespace
{
	struct IdentifierArray
	{
		std::array<size_t, 10> counts;
		std::array<vk::DescriptorType, 10> types;

		IdentifierArray()
		{
			counts.fill(0);
			for (size_t i = 0; i < 10; i++)
			{
				vk::DescriptorType type = static_cast<vk::DescriptorType>(i);
				types[i] = type;
			}
		}
	};

}


namespace vkUtil
{

	DescriptorSetOutBundle create_descriptor_set(const std::vector<DescriptorSetInBundle>& input)
	{
		std::vector<vk::DescriptorSetLayoutBinding> layoutBindings; 

		IdentifierArray arr;
		for (const auto& bundle : input) 
		{
			for (const auto& binding : bundle.bindings) 
			{
				layoutBindings.push_back(create_descriptor_set_layout_binding(binding)); 

				auto it = std::find(arr.types.begin(), arr.types.end(), binding.type);
				if (it != arr.types.end())
				{
					arr.counts[SIZET(*it)]++;
				}

			}
		}

		std::vector<vk::DescriptorPoolSize> poolSizes;
		poolSizes.reserve(10);


		for (const auto& [i, item] : arr.counts | std::views::enumerate) 
		{
			if (item != 0)
			{
				vk::DescriptorPoolSize poolSize;
				poolSize.type = arr.types[i];
				poolSize.descriptorCount = item;
				poolSizes.push_back(poolSize);
			}
		}

		vk::DescriptorSetLayout layout = create_descriptor_set_layout(DescriptorSetInBundle::device, layoutBindings);
		vk::DescriptorPool pool = create_descriptor_pool(DescriptorSetInBundle::device, poolSizes, input.size());

		std::vector<vk::DescriptorSet> descriptorSets = create_descriptor_sets(DescriptorSetInBundle::device, pool, layout, input.size());

		return { descriptorSets, pool };

	}


	vk::DescriptorSetLayoutBinding create_descriptor_set_layout_binding(const DescriptorSetBindingBundle& input)
	{
		vk::DescriptorSetLayoutBinding layoutBinding;
		layoutBinding.binding = input.binding;
		layoutBinding.descriptorType = input.type;
		layoutBinding.descriptorCount = input.count;
		layoutBinding.stageFlags = enum_to_vk(input.stage);
		layoutBinding.pImmutableSamplers = input.sampler;

		return layoutBinding;
	}


	vk::DescriptorSetLayout create_descriptor_set_layout(const vk::Device& device, const std::vector<vk::DescriptorSetLayoutBinding>& input)
	{

		vk::DescriptorSetLayoutCreateInfo layoutInfo;
		layoutInfo.flags = vk::DescriptorSetLayoutCreateFlagBits();
		layoutInfo.bindingCount = input.size();
		layoutInfo.pBindings = input.data();
		
		try
		{
			return device.createDescriptorSetLayout(layoutInfo);
		}
		catch (vk::SystemError& err)
		{
			throw std::runtime_error("failed to create descriptor set layout!");
		}
		
	}




	vk::DescriptorPool create_descriptor_pool(vk::Device& device, const std::vector<vk::DescriptorPoolSize>& poolSizes, uint32_t maxSets)
	{
		vk::DescriptorPoolCreateInfo poolInfo; 
		poolInfo.flags = vk::DescriptorPoolCreateFlagBits(); 
		poolInfo.maxSets = maxSets; 
		poolInfo.poolSizeCount = UINT32(poolSizes.size());
		poolInfo.pPoolSizes = poolSizes.data(); 

		try
		{
			return device.createDescriptorPool(poolInfo); 
		}
		catch (vk::SystemError& err) 
		{
			throw std::runtime_error("failed to create descriptor pool!"); 
		}

	}

	std::vector<vk::DescriptorSet> create_descriptor_sets(const vk::Device& device, const vk::DescriptorPool& pool, const vk::DescriptorSetLayout& layout, uint32_t descriptorSetCount)
	{
		vk::DescriptorSetAllocateInfo allocInfo; 
		allocInfo.descriptorPool = pool; 
		allocInfo.descriptorSetCount = descriptorSetCount; 
		allocInfo.pSetLayouts = &layout; 


		try
		{
			return device.allocateDescriptorSets(allocInfo); 
		}
		catch (vk::SystemError& err)
		{
			throw std::runtime_error("failed to allocate descriptor sets!");
		}
	}


} // namespace vkUtil