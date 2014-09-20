#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "buffer/Buffer.h"
#include "components/Camera.h"
#include "control/Arcball.h"
#include "pipeline/Pipeline.h"
#include "shader/Shader.h"

using namespace std;

struct VertexData {
	glm::vec4 pos;
	glm::vec4 norm;
};

void error_callback(int error, const char* description) {
	cerr << description << endl;
}

void checkGLError() {
	int error = glGetError();
	string estr;
	switch (error) {
	case GL_NO_ERROR:
		estr = "GL_NO_ERROR";
		break;
	case GL_INVALID_ENUM:
		estr = "GL_INVALID_ENUM";
		break;
	case GL_INVALID_VALUE:
		estr = "GL_INVALID_VALUE";
		break;
	case GL_INVALID_OPERATION:
		estr = "GL_INVALID_OPERATION";
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		estr = "GL_INVALID_FRAMEBUFFER_OPERATION";
		break;
	case GL_OUT_OF_MEMORY:
		estr = "GL_OUT_OF_MEMORY";
		break;
	case GL_STACK_UNDERFLOW:
		estr = "GL_STACK_UNDERFLOW";
		break;
	case GL_STACK_OVERFLOW:
		estr = "GL_STACK_OVERFLOW";
		break;
	}
    if (error) cout << "error = " << estr << endl;

}

int main(int argc, char *argv[]) {
	int windowWidth = 800, windowHeight = 600;


	/*
	 * initialise glfw window first
	 */
	if (!glfwInit()) exit(EXIT_FAILURE);
	glfwSetErrorCallback(error_callback);
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Window", NULL, NULL);
	glfwMakeContextCurrent(window);

	/*
	 * initialize glew after
	 */
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
    Pipeline pipeline;
    pipeline.addStage(test_vert, GL_VERTEX_SHADER_BIT);
    pipeline.addStage(test_frag, GL_FRAGMENT_SHADER_BIT);

    // Random Vertex Data
    vector<VertexData> verts;
    VertexData a;
    a.pos.x = -8;
    a.pos.y = 8;
    a.pos.z = -8;
    a.pos.w = 1.0;

    VertexData b;
    b.pos.x = 5;
    b.pos.y = -5;
    b.pos.z = -8;
    b.pos.w = 1.0;

    VertexData c;
    c.pos.x = -5;
    c.pos.y = -5;
    c.pos.z = -8;
    c.pos.w = 1.0;

    verts.push_back(a);
    verts.push_back(b);
    verts.push_back(c);
    Buffer<VertexData> buff(GL_ARRAY_BUFFER, verts);

    /*
     * camera viewpoint object
     */
    Camera camera;
    camera.resize(windowWidth, windowHeight);

    Arcball arcball(windowWidth, windowHeight);



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
			double oldx = mousex;
			double oldy = mousey;
			glfwGetCursorPos(window, &mousex, &mousey);
			if (mDown) {
				glm::quat q = arcball.mouseDragged(oldx, oldy, mousex, mousey);
				camera.rotate(q);
			}
			mDown = true;
		}
		else {
			mDown = false;
		}

		/*
		 * update camera and bind
		 */
		camera.update(0.01);
		camera.properties()->bind(pipeline.get("Camera"));



		/*
		 * attach buffers and give 2 attribute pointers
		 *
		 */
		glBindBuffer( GL_ARRAY_BUFFER, buff.location );
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void *)(0*sizeof(glm::vec4)));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void *)(1*sizeof(glm::vec4)));

		/*
		 * draw test
		 */
		glBindProgramPipeline(pipeline.name);
		glDrawArrays(GL_TRIANGLES, 0, 6400*3);

		glFlush();
		glfwSwapBuffers(window);


		checkGLError();
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
