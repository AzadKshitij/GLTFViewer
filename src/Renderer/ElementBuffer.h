#pragma once
#include <glad/glad.h>

class ElementBuffer
{
public:
	GLuint ID;
	ElementBuffer(GLuint* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();


};