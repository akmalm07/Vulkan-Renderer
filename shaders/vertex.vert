#version 450

layout(location = 0) in vec2 pos;  
layout(location = 1) in vec3 color;

layout (location = 0) out vec3 fragColor;

layout (push_constant) uniform constants 
{
	mat4 model;  
} objectData;


 void main()
 {
	gl_Position = objectData.model * vec4(pos, 0.0f, 1.0f); 
	fragColor = color;
}
