#pragma once

namespace Hazel {
	
	class Shader
	{
	public:
		virtual void CreateVertexShader() = 0;
		virtual void CreateFragmentShader() = 0;
		virtual void CreateShaderProgram() = 0;
		virtual void UseShader() = 0;
	};
}