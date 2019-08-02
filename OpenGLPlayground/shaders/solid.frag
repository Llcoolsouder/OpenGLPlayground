/**
 * @file solid.frag
 * 
 * Fragment shader which takes in a vec4 color and outputs the unmodified color
 *
 * @author Lonnie L. Souder II
 * @date 08/01/2019
 */
#version 430 core

/** A vec4 color input from the vertex shader */
in VERT_DATA {
	vec4 vColor;
} frag_in;

/** A vec4 color output to write to the display buffer */
out vec4 fFragColor;

void main()
{
	fFragColor = frag_in.vColor;
}