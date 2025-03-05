#include "headers.h"
#include "vkUtil/include/render_structs.h"
#include "vkUtil/include/shader.h"
#include "vkInit/include/push_constants.h"


namespace vkUtil 
{


	ObjectData::ObjectData(ShaderStage shader) 
		: PushConst(sizeof(data), vkInit::evaluate_offset_push_const(sizeof(data)), enum_to_vk(shader)) 
	{
	}


} // namespace vkUtil
