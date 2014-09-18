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

	void addStage(Shader &, GLbitfield);

	uint get(string);

private:
	uint bindings;
	map<string, uint> binds;

};

} /* namespace std */
#endif /* PIPELINE_H_ */
