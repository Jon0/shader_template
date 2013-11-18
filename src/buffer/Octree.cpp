/*
 * Texture.cpp
 *
 *  Created on: 20/11/2013
 *      Author: remnanjona
 */

#include "Octree.h"

namespace std {

Octree::Octree(unsigned int l) {
	levels = l;
	glGenTextures(1, &addr);
	glBindTexture(GL_TEXTURE_3D, addr);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, levels, levels, levels, 0, GL_RGBA,
	             GL_FLOAT, 0);

	//glGenerateMipmap(GL_TEXTURE_3D);

}

Octree::~Octree() {
	// TODO Auto-generated destructor stub
}

void Octree::bind(GLuint i) {
	glBindImageTexture(i, addr, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);
}

} /* namespace std */
