#pragma once
#include <glad/glad.h>

class VertexBuffer
{
	public:
		GLuint ID;
		VertexBuffer(GLfloat* vertices, GLsizeiptr size);

		// Binds the VBO
		void Bind();
		// Unbinds the VBO
		void Unbind();
		// Deletes the VBO
		void Delete();


};