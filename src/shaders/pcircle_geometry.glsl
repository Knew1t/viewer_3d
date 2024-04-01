#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

flat out vec4 center;
out vec4 fPos;

uniform float  u_point_size;
uniform vec2 u_viewport;

void main()
{
    center = gl_in[0].gl_Position;
    vec2 dir = normalize(vec2(u_viewport.y, u_viewport.x)/center.w)*u_point_size/500.0;

    gl_Position = gl_in[0].gl_Position + vec4(dir, 0.0, 0.0)*center.w;
    fPos = gl_Position;
    EmitVertex();

    dir.y = -dir.y;
    gl_Position = gl_in[0].gl_Position + vec4(dir, 0.0, 0.0)*center.w;
    fPos = gl_Position;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position - vec4(dir, 0.0, 0.0)*center.w;
    fPos = gl_Position;
    EmitVertex();
    
    dir.y = -dir.y;
    gl_Position = gl_in[0].gl_Position - vec4(dir, 0.0, 0.0)*center.w;
    fPos = gl_Position;
    EmitVertex();


    EndPrimitive();
}
// square drawing
    