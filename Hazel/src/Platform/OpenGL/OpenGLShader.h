#pragma once

#include "Hazel/Renderer/Shader.h"

namespace Hazel {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader();
		virtual void CreateVertexShader() override;
		virtual void CreateFragmentShader() override;
		virtual void CreateShaderProgram() override;
		virtual void UseShader() override;
	
	private:
		unsigned int m_ShaderProgram, m_VertexShader, m_FragmentShader;
	};
}
