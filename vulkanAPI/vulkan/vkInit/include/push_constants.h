#pragma once

#include "config.h"

namespace vkInit
{
	std::vector<vk::PushConstantRange> evaluate_push_constants(const std::vector<vkType::PushConst>& pushConsts, bool debug);

	vk::PushConstantRange create_push_constant(uint32_t offset, uint32_t size, vk::ShaderStageFlagBits shader, bool debug);

	uint32_t evaluate_offset_push_const(size_t size);
}