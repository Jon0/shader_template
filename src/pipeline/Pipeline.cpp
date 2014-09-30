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
}

Pipeline::~Pipeline() {
	glDeleteProgramPipelines(1, &name);
}

void Pipeline::setStage(GLuint program, GLbitfield stages) {

	/*
	 * add stage to pipeline
	 */
	glBindProgramPipeline(name);
	glUseProgramStages( name, stages, program);
}

GLuint Pipeline::makeProgram(Shader &s) {
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
			// bind to next value
			bind_point = bindings++;
			binds[attname] = bind_point;
		}
		else {
			bind_point = binds[attname];
		}

		// set the binding
		glShaderStorageBlockBinding( program, block_index, bind_point );
		cout << " -- storage block: " << attname << " bound to " << bind_point << endl;
	}

	/*
	 * list uniforms in shader
	 */
	glGetProgramInterfaceiv(program, GL_UNIFORM, GL_ACTIVE_RESOURCES, &num_blocks);
	for (int i = 0; i < num_blocks; ++i) {
		glGetProgramResourceName(program, GL_UNIFORM, i, 32, &len, attname );
		GLuint uniform_index = glGetUniformLocation( program, attname );

		// check if the name is already mapped
		if(binds.find(attname) == binds.end()) {
			binds[attname] = uniform_index;
		}
		cout << " -- uniform: " << attname << " bound to " << uniform_index << endl;
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
	 * if everything worked
	 */
	stage.push_back( program );
	return program;
}

uint Pipeline::get(string s) {
	return binds[s];
}

} /* namespace std */
