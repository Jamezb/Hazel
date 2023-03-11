#include "hzpch.h"
#include "Application.h"


#include "Hazel/Log.h"

#include <glad/glad.h>

#include "Input.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLRenderTriangle.h"


namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		// create ImGui layer.
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_Shader = new OpenGLShader();

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		unsigned int indices[3] = { 0, 1, 2 };
		
		m_Triangle = new OpenGLRenderTriangle(vertices, indices,sizeof(vertices),sizeof(indices));

		
	}


	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		// first part only handles window closing
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowCLose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			// Changes the value of it while also passing it to OnEvent, this will go last-first layer

			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running) 
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->UseShader();
			m_Triangle->DrawVertices();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

		     m_ImGuiLayer->Begin();
			 for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			 m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowCLose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer) 
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
}