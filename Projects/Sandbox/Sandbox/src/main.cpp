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
		// Update
		m_CameraController.OnUpdate(deltaT);

		// Render
		Nitrogen::Renderer2D::ResetStats();
		{
			NTG_PROFILE_SCOPE("Renderer Prep");
			Nitrogen::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			Nitrogen::RendererCommand::Clear();
		}

		{
			static float rotation = 0.0f;
			rotation += deltaT * 50.0f;

			NTG_PROFILE_SCOPE("Renderer Draw");
			Nitrogen::Renderer2D::BeginScene(m_CameraController.GetCamera());
			Nitrogen::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
			Nitrogen::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
			Nitrogen::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
			Nitrogen::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_Texture2d, 10.0f);
			Nitrogen::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_Texture2d, 20.0f);
			Nitrogen::Renderer2D::EndScene();

			Nitrogen::Renderer2D::BeginScene(m_CameraController.GetCamera());
			for (float y = -5.0f; y < 5.0f; y += 0.5f)
			{
				for (float x = -5.0f; x < 5.0f; x += 0.5f)
				{
					glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.4f };
					Nitrogen::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
				}
			}
			Nitrogen::Renderer2D::EndScene();
		}
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Stats");
		
		auto stats = Nitrogen::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();
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