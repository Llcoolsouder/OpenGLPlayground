#version 430 core

layout(location = 0) in vec3 uPosition;

out vec4 vColor;

void main()
{
	gl_Position = vec4(uPosition, 1);
	vColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}