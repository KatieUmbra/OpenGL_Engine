#version 460 core

layout(location = 0) out vec4 color;

uniform sampler2D u_texture;

in vec2 v_texture_coordinate;

void main()
{
    vec4 texture_color = texture(u_texture, v_texture_coordinate);
    color = texture_color;
}
