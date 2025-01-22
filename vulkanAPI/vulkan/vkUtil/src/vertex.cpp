#include "pch.h"

#include "vertex.h"


template struct VertexT<glm::vec2, glm::vec3, std::nullptr_t, std::nullptr_t>; 
template struct VertexT<glm::vec3, glm::vec4, std::nullptr_t, std::nullptr_t>; 
template struct VertexT<glm::vec3, glm::vec3, std::nullptr_t, std::nullptr_t>; 