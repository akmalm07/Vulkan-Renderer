#pragma once

#include <vulkan/vulkan.hpp>

#ifndef NDEBUG

#define VK_CHECK_RESULT(f) {																	\
		auto res = (f);																			\
		if (res != vk::Result::eSuccess) {														\
			std::cerr << "Fatal : VkResult is \"" << vk::to_string(res) << "\" in " << __FILE__	\
				<< " at line " << __LINE__ << std::endl;											\
			assert(res == vk::Result::eSuccess);													\
		}																						\
	}		\


#define DEBUG_ITERATOR(vec) \
for (const auto& item : vec) \
{ std::cout << " " << item << " "; } \
std::cout << "\n"; 


inline void check_vk_result(vk::Result result) 
{
	if (result != vk::Result::eSuccess)
	{
		throw std::runtime_error("Vulkan Error: " + vk::to_string(result) + "\n");
	}
}

#endif
