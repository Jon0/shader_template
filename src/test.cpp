#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GLFW/glfw3.h>

#include "shader/Shader.h"
#include "shader/program.h"
#include "config.h"

using namespace std;

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

int main() {
	cout << "hello version: " << Test_VERSION_MAJOR << "." << Test_VERSION_MINOR << endl;
	cout << sqrt(9) << endl;

	print();

	Shader s;


	if (!glfwInit()) exit(EXIT_FAILURE);

	glfwSetErrorCallback(error_callback);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
	glfwMakeContextCurrent(window);

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
