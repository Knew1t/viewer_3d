#version 330 core
layout (location = 0) in vec3 in_pos;

uniform float u_point_size;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    gl_PointSize = u_point_size;
    gl_Position = u_projection * u_view * u_model * vec4(in_pos.x, in_pos.y, in_pos.z, 1.0);
}
