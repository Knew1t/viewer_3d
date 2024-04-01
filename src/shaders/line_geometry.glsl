#version 330 core

layout(lines) in;
layout(triangle_strip, max_vertices=4) out;

out vec4 fPos;
flat out vec4 sPos;
out float edge_len;

uniform vec2 u_viewport;
uniform float u_thickness;

void main()
{
    vec4 p0 = gl_in[0].gl_Position;
    vec4 p1 = gl_in[1].gl_Position;

    edge_len = length((p1.xy/p1.w - p0.xy/p0.w) * u_viewport/2);  // screen space

    vec2 dir = normalize((p1.xy/p1.w - p0.xy/p0.w) * u_viewport/2);  // screen space
    vec4 offs = vec4(vec2(-dir.y, dir.x) * u_thickness * 0.5 / u_viewport, 0.0, 0.0);

    gl_Position = gl_in[0].gl_Position + offs*p0.w;
    fPos =  p0;
    sPos = fPos;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position - offs*p0.w;
    fPos =  p0;
    sPos = fPos;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position + offs*p1.w;
    fPos = p1;
    sPos = fPos;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position - offs*p1.w;
    fPos = p1;
    sPos = fPos;
    EmitVertex();

    EndPrimitive();
}
