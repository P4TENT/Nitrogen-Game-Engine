#include <Nitrogen.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

class ExampleLayer : public Nitrogen::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.f / 720.f)
	{
		m_Texture2d = Nitrogen::Texture2D::Create("src/assets/textures/2.png");
	}

	void OnUpdate(Nitrogen::Timestep deltaT) override
	{
		m_CameraController.OnUpdate(deltaT);

		Nitrogen::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Nitrogen::RendererCommand::Clear();

		Nitrogen::Renderer2D::BeginScene(m_CameraController.GetCamera());
		
		Nitrogen::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Nitrogen::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Nitrogen::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture2d, 1.0f, glm::vec4(0.9f, 0.8f, 0.8f, 1.0f));

		Nitrogen::Renderer2D::EndScene();

		if (Nitrogen::Input::IsKeyPressed(N_KEY_TAB))
		{
			NTG_CLIENT_FATAL("Tab Key Pressed!");
		}
		else if(Nitrogen::Input::IsKeyPressed(N_KEY_ESCAPE))
		{
			NTG_CLIENT_ERROR("Esc Key Pressed!");
		}
		else if (Nitrogen::Input::IsKeyPressed(N_KEY_CAPS_LOCK))
		{
			NTG_CLIENT_WARN("Caps Key Pressed!");
		}
		else if (Nitrogen::Input::IsKeyPressed(N_KEY_LEFT_SHIFT))
		{
			NTG_CLIENT_INFO("LShift Key Pressed!");
		}
		else if (Nitrogen::Input::IsKeyPressed(N_KEY_LEFT_CONTROL))
		{
			NTG_CLIENT_TRACE("LControl Key Pressed!");
		}
	}

	void OnImGuiRender() override
	{
	}

	void OnEvent(Nitrogen::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Nitrogen::Ref<Nitrogen::Texture2D> m_Texture2d;

	Nitrogen::OrthographicCameraController m_CameraController;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

class Sandbox : public Nitrogen::Application
{
public:
	Sandbox()
		: Application("Sandbox")
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