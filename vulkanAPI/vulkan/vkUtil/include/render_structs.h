#pragma once


#include "config.h"


namespace vkUtil {

	struct ObjectData : public vkType::Drawable, public vkType::PushConst 
	{
		glm::mat3 model; 
	};

	std::vector<vkType::Drawable*> renderedObjects = { new ObjectData{} };
}


