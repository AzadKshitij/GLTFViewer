#pragma once
#include <glad/glad.h>

class VertexBuffer
{
	public:
		GLuint ID;
		VertexBuffer(GLuint* vertices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();


};