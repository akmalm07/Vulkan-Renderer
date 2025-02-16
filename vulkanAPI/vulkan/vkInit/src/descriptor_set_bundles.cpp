#pragma once

#include "pch.h"

#include "vkInit\include\descriptor_set_bundles.h"

namespace vkInit
{

    DescriptorSetBindingBundle::DescriptorSetBindingBundle() = default;


    DescriptorSetBindingBundle::DescriptorSetBindingBundle(vk::DescriptorType type, std::vector<vkUtil::ShaderStage> stage, uint32_t count, uint32_t binding, vk::Sampler* sampler)
        : type(type), stage(stage), count(count), binding(binding), sampler(sampler)
    {
    }

    DescriptorSetBindingBundle::DescriptorSetBindingBundle(vk::DescriptorType type, vkUtil::ShaderStage stage, uint32_t count, uint32_t binding, vk::Sampler* sampler)
        : type(type), count(count), binding(binding), sampler(sampler)
    {
        this->stage.push_back(stage);
    }
}