#version 430

layout(std430, binding = 1) buffer Camera {
	mat4 P;
	mat4 V;
	mat4 M;
};

out vec4 color;

void main(){
	color = vec4(1.0);
}
