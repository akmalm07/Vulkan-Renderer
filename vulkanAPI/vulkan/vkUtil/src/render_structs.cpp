#include "pch.h"
#include "vkUtil/include/render_structs.h"
#include "vkUtil/include/shader.h"
#include "tools/include/const_push_registry.h"


namespace vkUtil 
{


	ObjectData::ObjectData(ShaderStage shader) 
		: PushConst(sizeof(data), tools::evaluate_offset_push_const(sizeof(data)), enum_to_vk(shader)) 
	{
	}


} // namespace vkUtil
