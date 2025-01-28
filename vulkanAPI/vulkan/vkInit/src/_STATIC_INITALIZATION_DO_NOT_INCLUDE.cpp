#include "pch.h"

#include "vkUtil\include\render_structs.h"
#include "vkUtil\include\const_pushes.h"


namespace
{
    struct _BEFORE_INT_MAIN_INIT_
    {
        _BEFORE_INT_MAIN_INIT_()
        {
            vkUtil::PushConstRegistery::get_instance().add_push_const(vkUtil::ObjectData(vkUtil::ShaderStage::VERTEX));
        }
    };

	static _BEFORE_INT_MAIN_INIT_ _initializer_; // This will be called before main
}