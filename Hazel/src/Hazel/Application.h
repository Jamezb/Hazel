#pragma once

#include "Core.h"

#include "Window.h"
#include "Hazel/LayerStack.h"
#include "Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/RenderTriangle.h"

namespace Hazel {
	  

	class HAZEL_API Application
		{
		public:
			Application();
			virtual ~Application();

			void Run();

			void OnEvent(Event& e);

			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);

			inline static Application& Get() { return *s_Instance; }

			inline Window& GetWindow() { return *m_Window; }
		private:
			bool OnWindowCLose(WindowCloseEvent& e);

			std::unique_ptr<Window> m_Window;
			ImGuiLayer* m_ImGuiLayer;
			bool m_Running = true;
			LayerStack m_LayerStack;
			Shader* m_Shader;
			RenderTriangle* m_Triangle;

			unsigned int m_VertexShader, m_FragmentShader, m_ShaderProgram,
				m_VertexArray, m_VertexBuffer, m_IndexBuffer;

		private:
			static Application* s_Instance;

		};


	// To be defined in CLIENT
	Application* CreateApplication();


}
