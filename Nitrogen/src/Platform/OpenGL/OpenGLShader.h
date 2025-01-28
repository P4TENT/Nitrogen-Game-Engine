#pragma once

#include "Nitrogen/Renderer/Shader.h"
#include <glm/glm.hpp>

//-TEMP--------------------
typedef unsigned int GLenum;
//-TEMP--------------------

namespace Nitrogen{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		OpenGLShader(const std::string& file_path);
		virtual ~OpenGLShader() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;
		virtual void SetMat3(const std::string& name, const glm::mat3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat(const std::string& name, float value) override;

		void UploadUniformMat4		(const std::string& name, const glm::mat4&	matrix);
		void UploadUniformMat3		(const std::string& name, const glm::mat3&	matrix);
		void UploadUniformFloat4	(const std::string& name, const glm::vec4&	value);
		void UploadUniformFloat3	(const std::string& name, const glm::vec3&	value);
		void UploadUniformFloat2	(const std::string& name, const glm::vec2&	value);
		void UploadUniformFloat		(const std::string& name, const float		value);
		void UploadUniformInt		(const std::string& name,		int			value);
		void UploadUniformIntArray	(const std::string& name,		int*		values, uint32_t count);

		virtual const std::string& GetName() const override { return m_Name; }
	
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(std::string& shaderSrc);
		void CompileShader(const std::unordered_map<GLenum, std::string>& shaderSrcs);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}