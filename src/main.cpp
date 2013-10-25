/*
 * main.cpp
 *
 *  Created on: 25/10/2013
 *      Author: remnanjona
 */

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

int main() {
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
	}


	return 0;
}


