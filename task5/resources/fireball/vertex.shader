#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 vertex_uv;
layout(location = 3) in mat4 model_matrix;  // mat4 = 4 x vec4. It utilizes locations 3,4,5,6
uniform mat4 vp;
out vec2 uv;

void main() {
    gl_Position = vp * model_matrix * vec4(position, 1);
    uv = vertex_uv;
}
