#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertex_position;

// Values that stay constant for the whole mesh.
uniform mat4 mvp;

void main(){
    gl_Position = mvp * vec4(vertex_position, 1);
}
