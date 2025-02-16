#pragma once 

#include "config.h"

#include "vkInit\include\discription.h"
#include "vkUtil\include\render_structs.h"
#include "vkUtil\include\vertex.h" 
#include "vkUtil\include\pipeline_bundles.h" 
#include "vkInit\include\push_constants.h" 




namespace vkInit 
{

	GraphicsPipelineOutBundle create_pipeline(GraphicsPipelineInBundle& spesifications, bool debug);
	
	vk::PipelineLayout create_pipeline_layout(vk::Device& logicalDevice, const std::vector<vk::DescriptorSetLayout>& layouts, const std::vector<vkType::PushConst>& pushs, bool debug);

	vk::RenderPass create_render_pass(vk::Device& logicalDevice, vk::Format format, bool debug);

}
