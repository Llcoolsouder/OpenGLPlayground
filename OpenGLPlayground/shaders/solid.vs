#version 410

layout(location = 0) in vec3 uPosition;

out vec4 vColor;

void main()
{
	gl_Position = vec4(uPosition, 1);
	vColor = vec4(0.5f, 0.0f, 1.0f, 1.0f);
}