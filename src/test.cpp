#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader/Shader.h"
#include "shader/program.h"
#include "config.h"

using namespace std;

void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void printVersion() {
	cout << "shader_test version: " << Test_VERSION_MAJOR << "." << Test_VERSION_MINOR << endl;
	print();
}

int main() {
	if (!glfwInit()) exit(EXIT_FAILURE);

	glfwSetErrorCallback(error_callback);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Init
    Shader s;

	while (!glfwWindowShouldClose(window))
	{
	    // Keep running

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
