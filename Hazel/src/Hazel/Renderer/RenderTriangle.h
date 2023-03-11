#pragma once

namespace Hazel {
	
	class RenderTriangle
	{
	public:
		virtual void VertexArray() = 0;
		virtual void IndexArray() = 0;
		virtual void DrawVertices() = 0;
	};
}