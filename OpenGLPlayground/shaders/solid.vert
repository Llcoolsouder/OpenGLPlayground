/**
 * @file solid.vert
 * 
 * Vertex shader which takes in a set of vec4 positions
 * and outputs the unmodified position and a uniform color
 *
 * @author Lonnie L. Souder II
 * @date 08/01/2019
 */
#version 430 core

/** The camera projection matrix */
uniform mat4 uProjMatrix = mat4(1.0f);

/** The camera view matrix */
uniform mat4 uViewMatrix = mat4(1.0f);

/** The model matrix (specifies model position and orientation */
uniform mat4 uModelMatrix = mat4(1.0f);

/** A vec4 specifying the color of all vertices that pass through this shader */
uniform vec4 uColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); 

/** A vec4 specifying position of the vertex; The only input for this shader */
layout(location = 0) in vec4 aPosition;

/** A vec4 color to be passed on to the fragment shader */
out vec4 vColor;

void main()
{
	gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * aPosition;
	vColor = uColor;
}