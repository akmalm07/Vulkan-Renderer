#pragma once

#include "config.h"
#include "std_types.h"
#include "scene.h"
 
template <Struct Parameter> 
using SScene = Scene <typename Parameter::Position, typename Parameter::Color, 
	typename Parameter::Normal, typename Parameter::Texture>; 


namespace vkType {

	using sscene = SScene< VertStd< pos, col, norm, tex>> ;

}

