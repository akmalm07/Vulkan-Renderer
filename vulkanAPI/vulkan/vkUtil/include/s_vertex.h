#pragma once

#include "std_types.h"

#include "vertex.h"
#include "std_types.h"



template <Struct Parameter>
using SVertex = Vertex<typename Parameter::Position, typename Parameter::Color, 
	typename Parameter::Normal, typename Parameter::Texture>;



namespace vkType {

	using Svertex = SVertex<VertStd<pos, col, norm, tex>>; 

}

