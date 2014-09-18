#version 430

layout(std430) buffer Camera {
	mat4 P;
	mat4 V;
	mat4 M;
};

layout(std430) buffer AnotherBuffer {
	vec4 something;
};

layout(binding = 0, rgba8) coherent uniform image3D voxel;

in vec4 color_vert;
out vec4 color;

void main(){
	color = color_vert;
}
