#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>


#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "buffer/Buffer.h"
#include "components/Camera.h"
#include "control/Arcball.h"
#include "pipeline/Pipeline.h"
#include "shader/Shader.h"
#include "vertex.h"

using namespace std;

/*
 * glfw error handling
 */
void error_callback(int error, const char* description) {
	cerr << description << endl;
}

/*
 * output gl error on cout
 */
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetErrorCallback(error_callback);
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Window", NULL, NULL);
	glfwMakeContextCurrent(window);


	/*
	 * Init vao for rendering
	 */
    GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

    /*
     * Load shaders and initialise pipeline
     */
    Shader test_vert("glsl/test.vert", GL_VERTEX_SHADER);
    Shader test_frag("glsl/test.frag", GL_FRAGMENT_SHADER);
    Pipeline pipeline;
    GLuint vshader = pipeline.makeProgram(test_vert);
    GLuint fshader = pipeline.makeProgram(test_frag);
    pipeline.setStage(vshader, GL_VERTEX_SHADER_BIT);
    pipeline.setStage(fshader, GL_FRAGMENT_SHADER_BIT);

    /*
     * Create random Triangle verticies and store in buffer
     */
    vector<VertexData> verts;
    VertexData a = makeVert(glm::vec4(-8, 8, -8, 1));
    VertexData b = makeVert(glm::vec4(5, -5, -8, 1));
    VertexData c = makeVert(glm::vec4(-5, -5, -8, 1));
    verts.push_back(a);
    verts.push_back(b);
    verts.push_back(c);
    Buffer<VertexData> buff(GL_ARRAY_BUFFER, verts);

    /*
     * camera viewpoint object
     */
    Camera camera;
    camera.resize(windowWidth, windowHeight);

    /*
     * arcball mouse control
     */
    Arcball arcball(windowWidth, windowHeight);

    /*
     * start main loop
     */
    bool mDown = false;
    double mousex, mousey;
	while (!glfwWindowShouldClose(window))
	{

		/*
		 * find the current dimensions of the window
		 */
	    int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		/*
		 * check for any mouse events
		 */
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
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glFlush();
		glfwSwapBuffers(window);

		checkGLError();
		glfwPollEvents();
	}

	/*
	 * clean up
	 */
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
