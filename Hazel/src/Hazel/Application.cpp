#include "hzpch.h"
#include "Application.h"


#include "Hazel/Log.h"

#include <glad/glad.h>



namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		// Confused by this
		// shouldn't I be able to access members of class like m_Data?
		// or not visible bc private?
		m_Window = std::unique_ptr<Window>(Window::Create());
		// set the callback function of m_Window to OnEvent
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
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
			// Calls the OnEvent for each layer - if handled then break
			// Currrently layer OnEvent defined in sandbox
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running) 
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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