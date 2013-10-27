/*
 * Buffer.h
 *
 *  Created on: 28/09/2013
 *      Author: remnanjona
 */

#ifndef BUFFER_H_
#define BUFFER_H_

namespace std {

class BufferBase {
public:
	virtual ~BufferBase() {}
};

template<class T> class Buffer: public BufferBase {
	GLuint location;
	GLenum type;
public:
	T data;

	Buffer(GLenum t) {
		type = t;
		glGenBuffers(1, &location);
		glBindBuffer(type, location);
		glBufferData(type, sizeof(T), &data, GL_STATIC_DRAW);
	}

	virtual ~Buffer() {
		glDeleteBuffers(1, &location);
	}
};

} /* namespace std */
#endif /* BUFFER_H_ */
