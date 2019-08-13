/**
 * @file point_to_circle.geom
 *
 * A geometry shader that will convert points to circles
 *
 * @author Lonnie L. Souder II
 * @date 08/02/2019
 */

#version 430 core

layout(points) in;
layout(triangle_strip, max_vertices=18) out;

in VERT_DATA {
	vec4 vColor;
} geom_in[];

out VERT_DATA {
	vec4 vColor;
} geom_out;

uniform mat4 ugProjMatrix = mat4(1.0f);
uniform mat4 ugViewMatrix = mat4(1.0f);

uniform float uScale = 0.05f;

const int MAX_VERTICES = 18;

/** Angle between consecutive points around the circle [degrees]*/
const float dTheta = 360.0f/((MAX_VERTICES-2)/2.0f);

/**
 * Converts point in worldspace to screen space
 *
 * @param point A point in world space
 * @return A point in screen space
 */
vec4 ToScreenSpace(vec4 point)
{
	return ugProjMatrix * ugViewMatrix * point;
}

/**
 * Returns the origin of the circle 
 *
 * @return The point that was passed to the geometry shader
 */
vec4 Origin()
{
// TODO: Transform to screen space after debug in worldspace
	return ToScreenSpace(gl_in[0].gl_Position);
}

/**
 * Calculates a unit vector rotated anti-cc about the origin
 *
 * @param theta Number of degrees to rotate around the origin
 * @return A unit vector rotated about the origin
 */
vec3 RotateUnitVecDegrees(float theta)
{
	float thetar = radians(theta);
	vec3 v = vec3(cos(thetar), sin(thetar), 0.0f);
	return v * uScale;
}

void main(void)
{
	float theta = 0.0f;
//	gl_Position = Origin();
//	geom_out.vColor = geom_in[0].vColor;
//	EmitVertex();
//	gl_Position = Origin() + vec4(RotateUnitVecDegrees(theta), 0.0f);
//	geom_out.vColor = geom_in[0].vColor;
//	EmitVertex();
	for(int i = 0; i < MAX_VERTICES/2; i++)
	{
		theta += dTheta;
		gl_Position = Origin() + vec4(RotateUnitVecDegrees(theta), 0.0f);
		geom_out.vColor = geom_in[0].vColor;
		EmitVertex();
		gl_Position = Origin();
		geom_out.vColor = geom_in[0].vColor;
		EmitVertex();
	}
	EndPrimitive();
}