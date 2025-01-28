#pragma once

#include "config.h"
#include "vkUtil\include\shader.h"

namespace vkUtil {


	struct ObjectData : public vkType::PushConst
	{
	public:
		ObjectData(ShaderStage shader);

		struct alignas(16) : public vkType::Drawable
		{
			glm::mat4 _model;
		} c_data;
	};



} // namespace vkUtil
