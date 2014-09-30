/*
 * Pipeline.h
 *
 *  Created on: 28/10/2013
 *      Author: remnanjona
 */

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <map>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../shader/Shader.h"

namespace std {

class Pipeline {
public:
	GLuint name;
	vector<GLuint> stage;

	Pipeline();
	virtual ~Pipeline();

	/*
	 * set the shader to draw with
	 */
	void setStage(GLuint, GLbitfield);

	/*
	 * create a new program for use with this pipeline
	 */
	GLuint makeProgram(Shader &);

	/*
	 * return bind point by name of shader variable
	 */
	uint get(string);

private:
	uint bindings;
	map<string, uint> binds;

};

} /* namespace std */
#endif /* PIPELINE_H_ */
