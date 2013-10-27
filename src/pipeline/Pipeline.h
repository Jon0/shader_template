/*
 * Pipeline.h
 *
 *  Created on: 28/10/2013
 *      Author: remnanjona
 */

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace std {

class Pipeline {
public:
	GLuint name;

	Pipeline();
	virtual ~Pipeline();
};

} /* namespace std */
#endif /* PIPELINE_H_ */
