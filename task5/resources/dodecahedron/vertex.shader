#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 3) in mat4 model_matrix;  // mat4 = 4 x vec4. It utilizes locations 3,4,5,6
uniform mat4 vp;
out vec3 fragment_color;

void main(){
    gl_Position = vp * model_matrix * vec4(position, 1);
    fragment_color = color;
}
