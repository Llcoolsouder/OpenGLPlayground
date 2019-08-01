#version 430 core

uniform vec4 uColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

layout(location = 0) in vec4 aPosition;

out vec4 vColor;

void main()
{
	gl_Position = aPosition;
	vColor = uColor;
}