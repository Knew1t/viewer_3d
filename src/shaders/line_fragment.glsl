#version 330 core

flat in vec4 sPos;
in vec4 fPos;
in float edge_len;

out vec4 fragColor;

uniform vec2  u_viewport;
uniform vec4  u_color;
uniform float  u_count;

void main()
{
    float dist = length((fPos.xy/fPos.w-sPos.xy/sPos.w) * u_viewport/2.0);
    float total_size = edge_len/u_count;

    if (fract(dist/total_size) > 0.5)
        discard;
    fragColor = u_color;
} 
