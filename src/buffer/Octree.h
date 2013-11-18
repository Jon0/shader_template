/*
 * Octree.h
 *
 *  Created on: 20/11/2013
 *      Author: remnanjona
 */

#ifndef OCTREE_H_
#define OCTREE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace std {

class Octree {
public:
	GLuint addr;
	unsigned int levels;

	Octree(unsigned int);
	virtual ~Octree();

	void bind(GLuint);
};

} /* namespace std */
#endif /* OCTREE_H_ */
