#version 450

layout(location = 0) in vec3 pos;  
layout(location = 1) in vec3 color;

layout (location = 0) out vec3 fragColor;

layout(set = 0, binding = 0) uniform UBO {
	mat4 model;
	mat4 view;
	mat4 proj;
} MVP;


 void main()
 {
	mat4 PVM = MVP.proj * MVP.view * MVP.model;
	gl_Position = PVM * vec4(pos, 1.0);
	fragColor = color;
}
