#version 430

layout(std430, binding = 1) buffer Camera {
	mat4 P;
	mat4 V;
	mat4 M;
};

layout(binding = 0, rgba8) coherent uniform image3D voxel;

in vec4 position_vert;
in vec4 color_vert;
out vec4 color;

void main(){
	color = color_vert;

	imageStore(voxel, ivec3(64, 64, 64) + ivec3(position_vert), color_vert);
}
