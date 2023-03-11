#pragma once

#include "Hazel/Renderer/RenderTriangle.h"

namespace Hazel {

	
	class OpenGLRenderTriangle : public RenderTriangle
	{
	public:
		OpenGLRenderTriangle(float(&vertices)[], unsigned int(&indices)[],
			unsigned int sizeVertices, unsigned int sizeIndices);
	private:
		virtual void VertexArray() override;
		virtual void IndexArray()  override;
		virtual void DrawVertices() override;

	private:
		float(&m_Vertices)[]; 
		unsigned int(&m_Indices)[];
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		unsigned int m_SizeVertices, m_SizeIndices;
	};
}