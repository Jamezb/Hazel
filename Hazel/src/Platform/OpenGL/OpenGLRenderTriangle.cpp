#include "hzpch.h"
#include "OpenGLRenderTriangle.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel {

	OpenGLRenderTriangle::OpenGLRenderTriangle(float(&vertices)[], unsigned int(&indices)[],
		unsigned int sizeVertices, unsigned int sizeIndices)
		:m_Vertices(vertices),m_Indices(indices),m_SizeVertices(sizeVertices),m_SizeIndices(sizeIndices)
	{
		VertexArray();
		IndexArray();
	}

	void OpenGLRenderTriangle::VertexArray()
	{
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		glBufferData(GL_ARRAY_BUFFER, m_SizeVertices, m_Vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	}

	void OpenGLRenderTriangle::IndexArray()
	{
		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_SizeIndices, m_Indices, GL_STATIC_DRAW);
	}

	void OpenGLRenderTriangle::DrawVertices()
	{
		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
	}
}