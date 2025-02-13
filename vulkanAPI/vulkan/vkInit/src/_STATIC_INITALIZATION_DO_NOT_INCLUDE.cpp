#include "pch.h"

#include "vkUtil\include\render_structs.h"
#include "tools\include\const_push_registry.h"
#include "vkUtil\include\descriptor_set.h"
#include "tools\include\json_reader.h"
#include "tools\include\descriptor_set_registry.h"


namespace
{
    struct _BEFORE_INT_MAIN_INIT_
    {
        _BEFORE_INT_MAIN_INIT_()
        {
			// make the push constant be defined via a JSON file
			//vkUtil::PushConstRegistery::get_instance().add_push_const(vkUtil::ObjectData(vkUtil::ShaderStage::VERTEX));
            // self calculates the size of the object

			JsonReader decriptorSet("descriptor_sets.json");

			std::vector<vkUtil::DescriptorSetInBundle> descriptorSets;

            for (const auto& set : decriptorSet["descriptor_sets"])
            {
				vkUtil::DescriptorSetInBundle bundle;
				bundle.descriptorSetCount = set["descriptor_set_count"];
				bundle.poolNumber = set["pool_number"];

				for (const auto& binding : set["bindings"])
				{
					bundle.bindings.emplace_back
					(
					vkUtil::to_descriptor_type(binding["descriptor_type"]),
					vkUtil::to_shader_stage(binding["stage_flags"]),
					binding["descriptor_count"],
					binding["binding"]
					);

				}

				descriptorSets.push_back(bundle);

            }

			std::vector<uint32_t> layouts;

			for (const auto& layout : decriptorSet["layouts"])
			{
				std::vector<vk::DescriptorSetLayoutBinding> layoutBindings;
					
				layouts.emplace_back(layout["binding_count"]);
			}


			tools::DescriptorSetRegistry::get_instance().intialize(descriptorSets, layouts);
        }

    };

	static _BEFORE_INT_MAIN_INIT_ _initializer_; // This will be called before main
}