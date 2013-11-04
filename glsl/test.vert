#version 430

layout(location = 0) in vec4 vertexPosition_modelspace;

layout(std430, binding = 1) buffer Camera {
	mat4 P;
	mat4 V;
	mat4 M;
};

out gl_PerVertex {
	vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
};

void main(){

	// cam.M * cam.V * cam.P *
	gl_Position = P * V * vertexPosition_modelspace;
}
