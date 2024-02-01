#include "VBO.h"

VBO::VBO(const void * data, GLsizeiptr size)
{
	// generate VBO buffer on the GPU
	glGenBuffers(1, &ID);

	// make VBO the current array buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	// copy vertex data from RAM to VRAM (to array buffer -> VBO)
	/*
		GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
		GL_STATIC_DRAW: the data is set only once and used many times.
		GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
	*/
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VBO::~VBO()
{
	this->Delete();
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
