#pragma once
#include <glad/glad.h>
#include <Renderer/VertexBuffer.h>

class VertexArray
{
	public:
		GLuint ID;
		VertexArray();

		void LinkVertexBufferObject( VertexBuffer& VBO, GLuint layout);
		void LinkAttribute( VertexBuffer& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset );
		void Bind();
		void Unbind();
		void Delete();
};