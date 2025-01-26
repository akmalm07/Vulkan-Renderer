#pragma once

#include "config.h"
#include "vkUtil\include\shader.h"

namespace vkUtil {


    struct ObjectData : public vkType::Drawable, public vkType::PushConst
    {
    public:
        ObjectData(ShaderStage shader);
        glm::mat4 _model;
    };



} // namespace vkUtil
