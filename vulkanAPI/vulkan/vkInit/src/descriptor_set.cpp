#include "headers.h"

#include "vkInit\include\descriptor_set.h"
#include "vkUtil\include\memory.h"


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


namespace vkInit
{

	DescriptorSetOutBundle create_descriptor_set(const vk::Device& device, const vk::PhysicalDevice& logicalDevice,
		const std::vector<DescriptorSetBindings>& descriptors, const std::vector<DescriptorSetBindings>& layouts,
		std::vector<vkInit::DescriptorBuffer> buffers, bool debug)
	{
		if (debug)
		{
			std::cout << "Creating Descriptor Set with " << descriptors.size() << " Descriptor Set Bundles" << std::endl;
		}

		std::vector<std::vector<vk::DescriptorSetLayoutBinding>> layoutBindings;

		IdentifierArray arr;
		for (const auto& layout : layouts)
		{
			std::vector<vk::DescriptorSetLayoutBinding> layoutBinding;
			for (const auto& binding : layout)
			{
				layoutBinding.emplace_back(create_descriptor_set_layout_binding(binding, debug));

				auto it = std::find(arr.types.begin(), arr.types.end(), binding.type);
				if (it != arr.types.end())
				{
					arr.counts[SIZET(*it)]++;
				}

			}
			layoutBindings.push_back(layoutBinding);

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

		vk::DescriptorPool pool = create_descriptor_pool(device, poolSizes, descriptors.size(), debug);

		std::vector<vk::DescriptorSetLayout> allLayout;

		for (const auto& descBindings : descriptors)
		{
			bool notexecuted = true;

			for (const auto& [i, layBindings] : layouts | std::views::enumerate)
			{
				//std::cout << "Desc: " << descBindings.size() << " == Lay: " << layBindings.size() << std::endl;
				if (descBindings.size() != layBindings.size())
				{
					continue;
				}

				bool allTrue = true;
				for (auto [descBinding, layoutBinding] : std::views::zip(descBindings, layBindings))
				{
					if (!(descBinding.type == layoutBinding.type && layoutBinding.count == descBinding.count))
					{
						allTrue = false;
						break;
					}
				}

				if (allTrue)
				{
					if (debug)
					{
						std::cout << "Creating Descriptor Set Layout with Bindings: " << std::endl;
						for (const auto& binding : layBindings)
						{
							std::cout << "\tBinding: " << binding.binding << " Type: " << vk::to_string(binding.type) << " Count: " << binding.count << std::endl;
						}
					}
					allLayout.emplace_back(create_descriptor_set_layout(device, layoutBindings[i], debug));
					notexecuted = false;
				}
			}
			if (notexecuted)
			{
				throw std::runtime_error("Layout count does not match binding count!"); // fix the binding count
			}
		}

		

		std::vector<vkUtil::Buffer> descriptorBuffer;
		for (size_t i = 0; i < buffers.size(); i++)
		{
			vkUtil::BufferInput bufferInfo;
			bufferInfo.size = buffers[i].maxSize;
			bufferInfo.usage = buffers[i].bufferType;

			descriptorBuffer.emplace_back(vkUtil::create_vk_util_buffer(logicalDevice, device, bufferInfo, 
				buffers[i].data, debug));
		}

		std::vector<vk::DescriptorSet> descriptorSets = create_descriptor_sets(device, pool, allLayout, descriptors.size(), debug);

		return { descriptorSets, allLayout, descriptorBuffer, pool };
	}

	vk::DescriptorSetLayoutBinding create_descriptor_set_layout_binding(const DescriptorSetBindingBundle& descriptors, bool debug)
	{
		if (debug) 
		{
			std::cout << "Creating Descriptor Set Layout Binding with binding: " << descriptors.binding << " Type: " << vk::to_string(descriptors.type) << " Count: " << descriptors.count << std::endl;
		}

		vk::DescriptorSetLayoutBinding layoutBinding;
		layoutBinding.binding = descriptors.binding;
		layoutBinding.descriptorType = descriptors.type; 
		layoutBinding.descriptorCount = descriptors.count;
		layoutBinding.stageFlags = vkUtil::mix_shader_flags_of_vector(descriptors.stage);

		layoutBinding.pImmutableSamplers = descriptors.sampler;

		return layoutBinding;
	}


	vk::DescriptorSetLayout create_descriptor_set_layout(const vk::Device& device, const std::vector<vk::DescriptorSetLayoutBinding>& layoutBindings, bool debug)
	{
		static std::vector<vk::DescriptorSetLayoutCreateInfo> check;
		static std::vector<vk::DescriptorSetLayout> allItems;

		vk::DescriptorSetLayoutBindingFlagsCreateInfo bindingFlagsCreateInfo = {};
		bindingFlagsCreateInfo.bindingCount = layoutBindings.size();
		
		vk::DescriptorBindingFlags* nextValues = new vk::DescriptorBindingFlags[layoutBindings.size()];
		for (size_t i = 0; i < layoutBindings.size(); i++)
		{
			nextValues[i] = vk::DescriptorBindingFlagBits::eUpdateAfterBind;
		}

		bindingFlagsCreateInfo.pBindingFlags = nextValues;


		vk::DescriptorSetLayoutCreateInfo layoutInfo;
		layoutInfo.flags = vk::DescriptorSetLayoutCreateFlagBits();
		layoutInfo.bindingCount = layoutBindings.size();
		layoutInfo.pBindings = layoutBindings.data();
		layoutInfo.pNext = &bindingFlagsCreateInfo;

		for (const auto& [i, checkLayout] : check | std::views::enumerate)
		{
			if (already_exists(checkLayout, layoutInfo))
			{
				return allItems[i];
			}
		}
		check.push_back(layoutInfo);

		
		try
		{
			allItems.push_back(device.createDescriptorSetLayout(layoutInfo));
			return allItems.back();
		}
		catch (vk::SystemError& err)
		{
			throw std::runtime_error("failed to create descriptor set layout!");
		}
		
	}




	vk::DescriptorPool create_descriptor_pool(const vk::Device& device, const std::vector<vk::DescriptorPoolSize>& poolSizes, uint32_t maxSets, bool debug)
	{

		if(debug)
		{
			std::cout << "Creating Descriptor Pool with sizes: " << std::endl;
			for (const auto& poolSize : poolSizes)
			{
				std::cout << "\tType: " << vk::to_string(poolSize.type) << " Count: " << poolSize.descriptorCount << std::endl;
			}
		}


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

	std::vector<vk::DescriptorSet> create_descriptor_sets(const vk::Device& device, const vk::DescriptorPool& pool, const std::vector<vk::DescriptorSetLayout>& layout, uint32_t descriptorSetCount, bool debug)
	{
		if (descriptorSetCount != layout.size())
		{
			throw std::runtime_error("Descriptor Set Count does not match Layout Count!");
		}
		if (debug)
		{
			std::cout << "Creating " << descriptorSetCount << " Descriptor Sets" << " with " << layout.size() << " Layouts" << std::endl;
		}

		vk::DescriptorSetAllocateInfo allocInfo; 
		allocInfo.descriptorPool = pool; 
		allocInfo.descriptorSetCount = descriptorSetCount; 
		allocInfo.pSetLayouts = layout.data(); 

		try
		{
			return device.allocateDescriptorSets(allocInfo); 
		}
		catch (vk::SystemError& err)
		{
			throw std::runtime_error("failed to allocate descriptor sets!");
		}
	}


	vk::DescriptorType to_descriptor_type(const std::string_view& type)
	{
		if (type == "sampler")
		{
			return vk::DescriptorType::eSampler;
		}
		else if (type == "combined_image_sampler")
		{
			return vk::DescriptorType::eCombinedImageSampler;
		}
		else if (type == "sampled_image")
		{
			return vk::DescriptorType::eSampledImage;
		}
		else if (type == "storage_image")
		{
			return vk::DescriptorType::eStorageImage;
		}
		else if (type == "uniform_texel_buffer")
		{
			return vk::DescriptorType::eUniformTexelBuffer;
		}
		else if (type == "storage_texel_buffer")
		{
			return vk::DescriptorType::eStorageTexelBuffer;
		}
		else if (type == "uniform_buffer")
		{
			return vk::DescriptorType::eUniformBuffer;
		}
		else if (type == "storage_buffer")
		{
			return vk::DescriptorType::eStorageBuffer;
		}
		else if (type == "uniform_buffer_dynamic")
		{
			return vk::DescriptorType::eUniformBufferDynamic;
		}
		else if (type == "storage_buffer_dynamic")
		{
			return vk::DescriptorType::eStorageBufferDynamic;
		}
		else if (type == "input_attachment")
		{
			return vk::DescriptorType::eInputAttachment;
		}
		else
		{
			throw std::runtime_error("Descriptor Type not found");
		}
	}

	vk::BufferUsageFlags to_buffer_type(const std::string_view& type)
	{
		if (type == "uniform")
		{
			return vk::BufferUsageFlagBits::eUniformBuffer;
		}
		else if (type == "storage")
		{
			return vk::BufferUsageFlagBits::eStorageBuffer;
		}
		else if (type == "vertex")
		{
			return vk::BufferUsageFlagBits::eVertexBuffer;
		}
		else if (type == "index")
		{
			return vk::BufferUsageFlagBits::eIndexBuffer;
		}
		else
		{
			throw std::runtime_error("Buffer Type not found");
		}
	}




	bool already_exists(const vk::DescriptorSetLayoutCreateInfo& check, const vk::DescriptorSetLayoutCreateInfo& toCheck)
	{
		if (check.bindingCount == toCheck.bindingCount)
		{
			for (size_t i = 0; i < check.bindingCount; i++)
			{
				if (check.pBindings[i].descriptorCount != toCheck.pBindings[i].descriptorCount || toCheck.pBindings[i].descriptorType != check.pBindings[i].descriptorType)
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}


} // namespace vkUtil