/*
 * Pipeline.cpp
 *
 *  Created on: 28/10/2013
 *      Author: remnanjona
 */

#include <iostream>

#include "Pipeline.h"

namespace std {

Pipeline::Pipeline() {
	bindings = 1;
	glGenProgramPipelines(1, &name);
	//glUseProgramStages
}

Pipeline::~Pipeline() {
	glDeleteProgramPipelines(1, &name);
}

void Pipeline::addStage(Shader &s, GLbitfield stages) {
	cout << "adding shader " << s.name << endl;

	/*
	 * create a program stage
	 */
	GLuint program = glCreateProgram();
	glAttachShader( program, s.ShaderHandle );
	glProgramParameteri( program, GL_PROGRAM_SEPARABLE, GL_TRUE );
	glLinkProgram( program );

	/*
	 * list available shader storage blocks
	 */
	int num_blocks;
	glGetProgramInterfaceiv(program, GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES, &num_blocks);

	int len;
	char attname [32];
	for (int i = 0; i < num_blocks; ++i) {
		glGetProgramResourceName(program, GL_SHADER_STORAGE_BLOCK, i, 32, &len, attname );
		GLuint block_index = glGetProgramResourceIndex( program, GL_SHADER_STORAGE_BLOCK, attname );

		// set binding point for attribute
		uint bind_point;

		// check if the name is already mapped
		if(binds.find(attname) == binds.end()) {
			bind_point = bindings++;
			glShaderStorageBlockBinding( program, block_index, bind_point ); // bind to next value
			binds[attname] = bind_point;
		}
		else {
			bind_point = binds[attname];
		}
		cout << " -- attribute: " << attname << " bound to " << bind_point << endl;
	}

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
	glUseProgramStages( name, stages, program);

	/*
	 * if everything worked
	 */
	stage.push_back( program );
}

uint Pipeline::get(string s) {
	return binds[s];
}

} /* namespace std */
