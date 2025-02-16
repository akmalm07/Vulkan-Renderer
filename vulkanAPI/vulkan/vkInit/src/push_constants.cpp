#include "pch.h"
#include "vkInit\include\push_constants.h"


namespace vkInit
{

	std::vector<vk::PushConstantRange> evaluate_push_constants(const std::vector<vkType::PushConst>& pushConsts, bool debug)
	{

		std::vector<vk::PushConstantRange> pushConstants;

		for (const auto& push : pushConsts)
		{
			std::cout << "Push constant offset: " << push._offset << " size: " << push._size << " shader: " << UINT32(push._shader) << "\n";
			pushConstants.emplace_back(create_push_constant(push._offset, push._size, push._shader, debug));
		}

		return pushConstants;
	}

	vk::PushConstantRange create_push_constant(uint32_t offset, uint32_t size, vk::ShaderStageFlagBits shader, bool debug)
	{
		vk::PushConstantRange pushConstantInfo = {};

		pushConstantInfo.offset = offset;

		pushConstantInfo.size = size;

		pushConstantInfo.stageFlags = shader;

		return pushConstantInfo;

	}

	[[nodiscard]] uint32_t evaluate_offset_push_const(size_t size)
	{
		static uint32_t s_offset = 0;
		static uint32_t s_size = 0;

		s_offset += s_size;

		s_size = size;

		if (s_offset == 0)
		{
			return 0;
		}

		return s_offset;
	}


}