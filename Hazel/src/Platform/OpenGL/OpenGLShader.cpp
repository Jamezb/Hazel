#include "hzpch.h"
#include "OpenGLShader.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

const char* VertexShaderSource = "#version 410 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* FragmentShaderSource = "#version 410 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";


namespace Hazel {

	OpenGLShader::OpenGLShader()
	{
		CreateVertexShader();
		CreateFragmentShader();
		CreateShaderProgram();
	}

	void OpenGLShader::CreateVertexShader()
	{
		m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_VertexShader, 1, &VertexShaderSource, NULL);
		glCompileShader(m_VertexShader);

	}

	void OpenGLShader::CreateFragmentShader()
	{
		m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_FragmentShader, 1, &FragmentShaderSource, NULL);
		glCompileShader(m_FragmentShader);
	}

	void OpenGLShader::CreateShaderProgram()
	{
		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, m_VertexShader);
		glAttachShader(m_ShaderProgram, m_FragmentShader);
		glLinkProgram(m_ShaderProgram);
		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);
	}

	void OpenGLShader::UseShader()
	{
		glUseProgram(m_ShaderProgram);
	}
}