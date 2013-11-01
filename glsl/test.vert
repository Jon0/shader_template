#version 420

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

out gl_PerVertex {
	vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
};

void main(){
	gl_Position =  M * V * P * vec4( vertexPosition_modelspace, 1 );
}
