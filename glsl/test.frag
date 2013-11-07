#version 430

layout(std430, binding = 1) buffer Camera {
	mat4 P;
	mat4 V;
	mat4 M;
};

in vec4 color_vert;
out vec4 color;

void main(){
	color = color_vert;
}
