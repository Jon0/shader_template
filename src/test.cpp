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
#include "pipeline/Pipeline.h"
#include "shader/Shader.h"
#include "config.h"

using namespace std;

struct silly_vect {
	glm::vec4 pos;
	glm::vec4 norm;
};

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
    Shader vert("glsl/test.vert", GL_VERTEX_SHADER);
    Shader frag("glsl/test.frag", GL_FRAGMENT_SHADER);

    Pipeline pipeline;
    pipeline.addStage(vert, GL_VERTEX_SHADER_BIT);
    pipeline.addStage(frag, GL_FRAGMENT_SHADER_BIT);

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
    Buffer<silly_vect> buff(GL_ARRAY_BUFFER, verts); //.data(), [verts]() -> GLsizeiptr { return verts.size(); }


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
	     * attach pipeline
	     */
		glBindProgramPipeline(pipeline.name);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glFlush();
		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
