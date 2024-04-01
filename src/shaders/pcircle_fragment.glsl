#version 330 core

flat in vec4 center;
in vec4 fPos;

out vec4 fragColor;

uniform float  u_point_size;
uniform vec2  u_viewport;
uniform vec4  u_color;

void main(void)
{
    float dist = length((fPos.xy/fPos.w - center.xy/center.w) * u_viewport/2.0);
    if (dist >= sqrt(u_point_size))
        discard;
    fragColor = u_color;
}