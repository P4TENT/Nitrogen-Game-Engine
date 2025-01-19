#pragma once

#include <glm/glm.hpp>

namespace Nitrogen{
	
	class OrthographicCamera 
	{
	public:
		OrthographicCamera(float left, float right, float top, float bottom);

		inline void SetPosition(const glm::vec3& position) 
		{ 
			m_Position = position; 
			RecalculateViewMatrix();
		}
		inline void SetRotation(float rotation) 
		{ 
			m_Rotation = rotation; 
			RecalculateViewMatrix();
		}

		inline const glm::vec3& GetPosition()		const { return m_Position; }
		inline const float GetRotation()			const { return m_Rotation; }

		const glm::mat4& GetProjectionMatrix()		const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix()			const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix()	const { return m_ViewProjMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.f;
	};

}
