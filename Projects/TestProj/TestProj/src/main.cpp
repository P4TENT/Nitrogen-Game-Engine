#include <Nitrogen.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

class ExampleLayer : public Nitrogen::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(glm::vec3(0.f))
	{
		m_VertexArray.reset(Nitrogen::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Nitrogen::Ref<Nitrogen::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Nitrogen::VertexBuffer::Create(vertices, sizeof(vertices)));
		Nitrogen::BufferLayout layout = {
			{ Nitrogen::ShaderDataType::Float3, "a_Position" },
			{ Nitrogen::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Nitrogen::Ref<Nitrogen::IndexBuffer> indexBuffer;
		indexBuffer.reset(Nitrogen::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Nitrogen::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Nitrogen::Ref<Nitrogen::VertexBuffer> squareVB;
		squareVB.reset(Nitrogen::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Nitrogen::ShaderDataType::Float3, "a_Position" },
			{ Nitrogen::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Nitrogen::Ref<Nitrogen::IndexBuffer> squareIB;
		squareIB.reset(Nitrogen::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Nitrogen::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string ColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string ColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}
		)";

		m_ColorShader = Nitrogen::Shader::Create("FlatColor", ColorShaderVertexSrc, ColorShaderFragmentSrc);

		std::string TexShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string TexShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		auto textureShader = m_ShaderLibrary.Load("src\\assets\\shaders\\Texture.glsl");

		NTG_CLIENT_INFO("INFO");

		m_Texture2d = Nitrogen::Texture2D::Create("src\\assets\\textures\\2.png");
		m_TransparentTex = Nitrogen::Texture2D::Create("src\\assets\\textures\\transparent.png");

		std::dynamic_pointer_cast<Nitrogen::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Nitrogen::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Nitrogen::Timestep deltaT) override
	{
		if (Nitrogen::Input::IsKeyPressed(N_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaT;
		else if (Nitrogen::Input::IsKeyPressed(N_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * deltaT;

		if (Nitrogen::Input::IsKeyPressed(N_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * deltaT;
		else if (Nitrogen::Input::IsKeyPressed(N_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaT;

		if (Nitrogen::Input::IsKeyPressed(N_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * deltaT;
		if (Nitrogen::Input::IsKeyPressed(N_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * deltaT;

		Nitrogen::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Nitrogen::RendererCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Nitrogen::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Nitrogen::OpenGLShader>(m_ColorShader)->Bind();
		std::dynamic_pointer_cast<Nitrogen::OpenGLShader>(m_ColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Nitrogen::Renderer::Submit(m_SquareVA, m_ColorShader, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture2d->Bind();
		Nitrogen::Renderer::Submit(m_SquareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_TransparentTex->Bind();
		Nitrogen::Renderer::Submit(m_SquareVA, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.f)));

		// Triangle Submit
		//Nitrogen::Renderer::Submit(m_VertexArray, m_Shader);

		Nitrogen::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		// Color Test With ImGui!
		ImGui::Begin("Test Settings");
		ImGui::ColorEdit4("Square Color: ", glm::value_ptr(m_SquareColor));
		ImGui::End();

	}

	void OnEvent(Nitrogen::Event& event) override
	{
	}

private:
	Nitrogen::ShaderLibrary m_ShaderLibrary;
	Nitrogen::Ref<Nitrogen::Shader> m_Shader;
	Nitrogen::Ref<Nitrogen::VertexArray> m_VertexArray;

	Nitrogen::Ref<Nitrogen::Shader> m_ColorShader;
	Nitrogen::Ref<Nitrogen::VertexArray> m_SquareVA;

	Nitrogen::Ref<Nitrogen::Texture2D> m_Texture2d, m_TransparentTex;

	Nitrogen::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

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