#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "buffer/Buffer.h"
#include "buffer/Octree.h"
#include "components/Camera.h"
#include "pipeline/Pipeline.h"
#include "shader/Shader.h"
#include "config.h"

using namespace std;

struct silly_vect {
	glm::vec4 pos;
	glm::vec4 norm;
};

Buffer<silly_vect> make_buffer(const char *filename) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename,
			aiProcess_CalcTangentSpace | aiProcess_Triangulate
			| aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

	cout << filename << " contains " << scene->mNumMeshes << " meshes" << endl;
	cout << filename << " contains " << scene->mNumMaterials << " materials" << endl;

	vector<silly_vect> verts;

	/* add each polygon */
	for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {

		/*
		 * copy data to the mesh
		 */
		aiMesh &mesh = *scene->mMeshes[m];
		cout << "num faces = " << mesh.mNumFaces << endl;
		cout << "has tangents = " << mesh.HasTangentsAndBitangents() << endl;

		for (unsigned int i = 0; i < mesh.mNumFaces; ++i) {

			for (unsigned int j = 0; j < mesh.mFaces[i].mNumIndices; ++j) {
				unsigned int ind = mesh.mFaces[i].mIndices[j];

				// copy vector data
			    silly_vect vect;
			    vect.pos.x = mesh.mVertices[ind].x;
			    vect.pos.y = mesh.mVertices[ind].y;
			    vect.pos.z = mesh.mVertices[ind].z;
			    vect.pos.w = 1.0;
			    verts.push_back(vect);


				/* tex coord if available */
				if (mesh.mNumUVComponents[0]) {
					aiVector3D &c = mesh.mTextureCoords[0][ind];

				}

				/* tangent and bitangent if available */
				if (mesh.HasTangentsAndBitangents()) {

				}
			}
		}
	}

	cout << "finish load" << endl;
	return Buffer<silly_vect>(GL_ARRAY_BUFFER, verts);
}

void error_callback(int error, const char* description) {
	cerr << description << endl;
}

void printVersion() {
	cout << "shader_test version: " << Test_VERSION_MAJOR << "." << Test_VERSION_MINOR << endl;
}

int main(int argc, char *argv[]) {
	if (!glfwInit()) exit(EXIT_FAILURE);

	glfwSetErrorCallback(error_callback);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Initialize GLEW
    if (glewInit() != GLEW_OK) {
    	cerr << "Failed to initialize GLEW" << endl;
        exit(EXIT_FAILURE);
    }

	/* Init vao */
    GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

    // Init Pipeline
    Shader test_vert("glsl/test.vert", GL_VERTEX_SHADER);
    Shader test_frag("glsl/test.frag", GL_FRAGMENT_SHADER);
    Shader voxel_vert("glsl/voxel.vert", GL_VERTEX_SHADER);
    Shader voxel_frag("glsl/voxel.frag", GL_FRAGMENT_SHADER);

    Pipeline voxel_pipeline;
    voxel_pipeline.addStage(voxel_vert, GL_VERTEX_SHADER_BIT);
    voxel_pipeline.addStage(voxel_frag, GL_FRAGMENT_SHADER_BIT);

    Pipeline pipeline;
    pipeline.addStage(test_vert, GL_VERTEX_SHADER_BIT);
    pipeline.addStage(test_frag, GL_FRAGMENT_SHADER_BIT);

    // Test Vertex Data
    vector<silly_vect> verts;
    silly_vect a;
    a.pos.x = -8;
    a.pos.y = 8;
    a.pos.z = -8;
    a.pos.w = 1.0;

    silly_vect b;
    b.pos.x = 5;
    b.pos.y = -5;
    b.pos.z = -8;
    b.pos.w = 1.0;

    silly_vect c;
    c.pos.x = -5;
    c.pos.y = -5;
    c.pos.z = -8;
    c.pos.w = 1.0;

    verts.push_back(a);
    verts.push_back(b);
    verts.push_back(c);
    //Buffer<silly_vect> buff(GL_ARRAY_BUFFER, verts); //.data(), [verts]() -> GLsizeiptr { return verts.size(); }

    // random model.
    Buffer<silly_vect> buff = make_buffer("model/Teapot.obj");

    /*
     * 3d buffer of voxels
     */
    Octree tree(128);

    /*
     * camera viewpoint
     */
    Camera camera;
    camera.resize(800, 600);
    camera.properties()->bind(1);

    /*
     * gl error check
     */
    if (int error = glGetError()) cout << "error = " << error << endl;

    /*
     * start loop
     */
    bool mDown = false;
    double mousex, mousey;
	while (!glfwWindowShouldClose(window))
	{
	    int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
			glfwGetCursorPos(window, &mousex, &mousey);

			if (!mDown) {
				camera.mouseClicked(0, 0, mousex, height-mousey);
			}
			else {
				camera.mouseDragged(mousex, height-mousey);
			}
			mDown = true;
		}
		else if (mDown) {
			camera.mouseClicked(0, 1, mousex, height-mousey);
			mDown = false;
		}

		/*
		 * update cam
		 */
		camera.update(0.01);
		camera.properties()->bind(1);

		/*
		 * attach buffers
		 */
		glBindBuffer( GL_ARRAY_BUFFER, buff.location );
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0*4));

	    /*
	     * attach voxel pipeline to produce voxel data
	     */
		glBindProgramPipeline(voxel_pipeline.name);
		glDrawArrays(GL_TRIANGLES, 0, 6400);

		/*
		 * draw voxels
		 */
		glBindProgramPipeline(pipeline.name);
		glDrawArrays(GL_TRIANGLES, 0, 6400*3);

		glFlush();
		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
