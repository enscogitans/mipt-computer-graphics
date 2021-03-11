#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertex_position;

void main(){
    gl_Position.xyz = vertex_position;
    gl_Position.w = 1.0;
}
