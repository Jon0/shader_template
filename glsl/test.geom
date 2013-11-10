#version 430
layout (points) in;
layout (triangle_strip,max_vertices=24) out;

smooth out vec4 oColor;
in VertexData
{
    vec4 colour;
    //vec3 normal;
} vertexData[];

layout(std430, binding = 1) buffer Camera {
	mat4 P;
	mat4 V;
	mat4 M;
};

const vec4 cubeVerts[8] = vec4[8](
    vec4(-0.5 , -0.5, -0.5,1),  //LB   0
     vec4(-0.5, 0.5, -0.5,1), //L T   1
    vec4(0.5, -0.5, -0.5,1), //R B    2
    vec4( 0.5, 0.5, -0.5,1),  //R T   3
                        //back face
    vec4(-0.5, -0.5, 0.5,1), // LB  4
     vec4(-0.5, 0.5, 0.5,1), // LT  5
    vec4(0.5, -0.5, 0.5,1),  // RB  6
     vec4(0.5, 0.5, 0.5,1)  // RT  7
    );

const int  cubeIndices[24]  = int [24]
    (
      0,1,2,3, //front
      7,6,3,2, //right
      7,5,6,4,  //back or whatever
      4,0,6,2, //btm
      1,0,5,4, //left
      3,1,7,5
    );

void main()
{
    vec4 temp;
    int a = int(vertexData[0].colour[3]);
    //btm face
    if (a>31)
    {
        for (int i=12;i<16; i++)
        {
            int v = cubeIndices[i];
            temp = modelToWorldMatrix * (gl_in[0].gl_Position + cubeVerts[v]);
            temp = worldToCameraMatrix * temp;
            gl_Position = cameraToClipMatrix * temp;
            //oColor = vertexData[0].colour;
            //oColor[3]=1;
            oColor=vec4(1,1,1,1);
            EmitVertex();
        }
        a = a - 32;
        EndPrimitive();
    }
    //top face
    if (a >15 )
...
}