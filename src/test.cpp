#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "pipeline/Pipeline.h"
#include "shader/Shader.h"
#include "config.h"

using namespace std;

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

    // Init pipeline
    Pipeline pipeline;
    Shader shader("glsl/test.vert", GL_VERTEX_SHADER);

    pipeline.addStage(shader);

    int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	while (!glfwWindowShouldClose(window))
	{
	    // Keep running
		glBindProgramPipeline(pipeline.name);

		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
