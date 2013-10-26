/*
 * Buffer.h
 *
 *  Created on: 28/09/2013
 *      Author: remnanjona
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <map>
#include <string>
#include <GL/gl.h>

namespace std {

class BufferBase {
public:
	virtual ~UniformControlBase() {}
	virtual void set(GLuint) = 0;
	virtual void unset() = 0;
};

template<class T> class BufferBase: public UniformControlBase {
	bool update;
	GLuint location;
	void (*setupFunc)(GLuint, T); //  = [](GLuint a, T b) {...}
public:
	T data;

	BufferBase(void (*f)(GLuint, T)) {
		update = false;
		location = 0;
		setupFunc = f;
	}

	virtual ~BufferBase() {}

	virtual void set(GLuint i) {
		update = true;
		location = i;
		setupFunc(i, data);
	}

	virtual void unset() {
		update = false;
	}


// TODO operator =
//	T &operator=(const BufferBase &u) {
//		T r(u);
//		return *r;
//	}
//
//	BufferBase &operator=(const T &v) {
//		data = v;
//		if (update) {
//			setupFunc(location, data);
//		}
//		return *this;
//	}

	void setV(T v) {
		data = v;
		if (update) {
			setupFunc(location, data);
		}
	}

	T getV() {
		return data;
	}

	void forceUpdate() {
		if (update) {
			setupFunc(location, data);
		}
	}
};

} /* namespace std */
#endif /* BUFFER_H_ */