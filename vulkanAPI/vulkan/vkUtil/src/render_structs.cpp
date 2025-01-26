#include "pch.h"
#include "vkUtil/include/render_structs.h"
#include "vkUtil/include/shader.h"
#include "vkUtil/include/const_pushes.h"


namespace vkUtil {


    ObjectData::ObjectData(ShaderStage  shader) 
        : PushConst(sizeof(*this), evaluate_offset_push_const(*this), enum_to_vk(shader))
    {}


} // namespace vkUtil
