/*
 * Pipeline.cpp
 *
 *  Created on: 28/10/2013
 *      Author: remnanjona
 */

#include "Pipeline.h"

namespace std {

Pipeline::Pipeline() {
	glGenProgramPipelines(1, &name);
	//glUseProgramStages

}

Pipeline::~Pipeline() {
	glDeleteProgramPipelines(1, &name);
}

} /* namespace std */
