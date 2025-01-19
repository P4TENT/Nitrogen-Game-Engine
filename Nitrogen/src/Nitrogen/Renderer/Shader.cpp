#include "ntgpch.h"

#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Nitrogen{
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:			NTG_CORE_ASSERT(false, "Nitro::Shader::Create(): 'RenderAPI::None' is currently not supported!");
		case RenderAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(name, vertexSource, fragmentSource);

		}

		NTG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& file_path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:			NTG_CORE_ASSERT(false, "Nitro::Shader::Create(): 'RenderAPI::None' is currently not supported!");
		case RenderAPI::API::OpenGL:		return std::make_shared<OpenGLShader>(file_path);

		}

		NTG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		NTG_CORE_ASSERT(!Exists(name), "Nitro::ShaderLibrary::Add(): Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}
	
	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}
	
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		NTG_CORE_ASSERT(Exists(name), "Nitro::ShaderLibrary::Get(): Shader not found!");
		return m_Shaders[name];
	}
	
	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}