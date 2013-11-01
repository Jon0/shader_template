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

void Pipeline::addStage(Shader &s) {

	/*
	 * create a program stage
	 */
	GLuint program = glCreateProgram();
	glAttachShader( program, s.ShaderHandle );
	glProgramParameteri( program, GL_PROGRAM_SEPARABLE, GL_TRUE );
	glLinkProgram( program );

	/*
	 * check errors
	 */
	int rvalue;
	glGetProgramiv( program, GL_LINK_STATUS, &rvalue );
	if (!rvalue) {
		fprintf(stderr, "Error in linking shader program\n");
		GLchar log[10240];
		GLsizei length;
		glGetProgramInfoLog( program, 10239, &length, log );
		fprintf(stderr, "Linker log:\n%s\n", log);
	}


	/*
	 * add stage to pipeline
	 */
	glBindProgramPipeline(name);
	glUseProgramStages( name, GL_VERTEX_SHADER_BIT, program);

	/*
	 * if everything worked
	 */
	stage.push_back( program );
}

} /* namespace std */
