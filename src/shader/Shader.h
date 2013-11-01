/*
 * Shader.h
 *
 *  Created on: 20/09/2013
 *      Author: remnanjona
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace std {

class Shader {
public:
	GLuint ShaderHandle;
	GLenum type;

	Shader(string, GLenum);
	virtual ~Shader();
};

} /* namespace std */
#endif /* SHADER_H_ */
