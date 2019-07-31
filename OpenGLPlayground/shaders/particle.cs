#version 430 core

layout (local_size_x = 1024, local_size_y = 1, local_size_z = 1) in;

layout(std140, binding=4) buffer aPos
{
    vec3 Positions[];
};

layout(std140, binding=5) buffer aVel
{
    vec3 Velocities[];
};

layout(std140, binding=6) buffer aCol
{
    vec4 Colors[];
};

void main()
{
    const vec3 G = vec3(0.0f, -9.8f, 0.0f);
    const float dT = 0.01;

    vec3 p = Positions[gl_GlobalInvocationID.x].xyz;
    vec3 v = Velocities[gl_GlobalInvocationID.x].xyz;

    // p' = p + vt + 1/2 G t^2
    vec3 pp = p + (v * dT) + (0.5f * dT * dT * G);

    // v' = v + Gt
    vec3 vp = v + (G * dT);

    Positions[gl_GlobalInvocationID.x] = pp;
    Velocities[gl_GlobalInvocationID.x] = vp;
}