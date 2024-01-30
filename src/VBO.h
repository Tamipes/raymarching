#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
public:
	GLuint ID;
	VBO(GLfloat *vertecies, GLsizeiptr size);
	~VBO();

	void Bind();
	void Unbind();
	void Delete();
};

#endif