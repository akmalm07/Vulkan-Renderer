#pragma once

#include "config.h"

namespace vkInit {

	vk::Semaphore make_semaphore(vk::Device& logicalDevice, bool debug);

	vk::Fence make_fence(vk::Device& logicalDevice, bool debug);
}