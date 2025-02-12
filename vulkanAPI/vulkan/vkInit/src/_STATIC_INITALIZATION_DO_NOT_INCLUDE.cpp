#include "pch.h"

#include "vkUtil\include\render_structs.h"
#include "vkUtil\include\const_pushes.h"


namespace
{
    struct _BEFORE_INT_MAIN_INIT_
    {
        _BEFORE_INT_MAIN_INIT_()
        {
			// make the push constant be defined via a JSON file
			//vkUtil::PushConstRegistery::get_instance().add_push_const(vkUtil::ObjectData(vkUtil::ShaderStage::VERTEX));
            // self calculates the size of the object


			//Add descritor set layout registery
        }

    };

	static _BEFORE_INT_MAIN_INIT_ _initializer_; // This will be called before main
}