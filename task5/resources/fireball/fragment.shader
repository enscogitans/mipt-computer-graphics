#version 330 core

in vec2 uv;
uniform sampler2D texture_sampler;
out vec3 color;

void main() {
    color = texture(texture_sampler, uv).rgb;  // Output color = color of the texture at the specified UV
}
