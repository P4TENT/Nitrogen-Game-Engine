#include <Nitrogen.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Nitrogen::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.f / 720.f)
	{
	}

	void OnUpdate(Nitrogen::Timestep deltaT) override
	{
		m_CameraController.OnUpdate(deltaT);

		Nitrogen::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Nitrogen::RendererCommand::Clear();

		Nitrogen::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Nitrogen::Renderer2D::DrawQuad({ -1.f, 0.f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.2f , 1.f });
		Nitrogen::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.2f, 0.8f , 1.f });

		Nitrogen::Renderer2D::EndScene();
	}

	void OnImGuiRender() override
	{
	}

	void OnEvent(Nitrogen::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}


private:
	Nitrogen::ShaderLibrary m_ShaderLibrary;
	Nitrogen::Ref<Nitrogen::VertexArray> m_VertexArray;

	Nitrogen::Ref<Nitrogen::Shader> m_ColorShader;
	Nitrogen::Ref<Nitrogen::VertexArray> m_SquareVA;

	Nitrogen::Ref<Nitrogen::Texture2D> m_Texture2d, m_TransparentTex;

	Nitrogen::OrthographicCameraController m_CameraController;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.f };
};

class Sandbox : public Nitrogen::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Nitrogen::Application* Nitrogen::CreateApplication()
{
	return new Sandbox();
}