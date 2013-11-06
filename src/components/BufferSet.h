/*
 * BufferSet.h
 *
 *  Created on: 6/11/2013
 *      Author: remnanjona
 */

#ifndef BUFFERSET_H_
#define BUFFERSET_H_

#include <memory>
#include <string>

#include "Component.h"

namespace std {

class BufferSet {
public:
	BufferSet();
	virtual ~BufferSet();
	shared_ptr<Component> lookup( string );
};

} /* namespace std */
#endif /* BUFFERSET_H_ */
