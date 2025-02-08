#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Nitrogen {

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip)
			: m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip),
			m_Position(0.0f, 0.0f, 3.0f), m_Yaw(-90.0f), m_Pitch(0.0f), m_Front(0.0f, 0.0f, -1.0f), m_Up(0.0f, 1.0f, 0.0f)
		{
			RecalculateViewMatrix();
			RecalculateProjectionMatrix();
		}

		// Set position
		void SetPosition(const glm::vec3& position);
		void SetRotation(float yaw, float pitch);
		void SetProjection(float fov, float aspectRatio, float nearClip, float farClip);

		// Getters
		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline float GetYaw() const { return m_Yaw; }
		inline float GetPitch() const { return m_Pitch; }

		inline const glm::vec3& GetFront() { return m_Front; }

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjMatrix; }

	private:
		void RecalculateViewMatrix()
		{
			// Calculate the front vector from yaw and pitch
			glm::vec3 front;
			front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
			front.y = sin(glm::radians(m_Pitch));
			front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
			m_Front = glm::normalize(front);

			// Recalculate view matrix
			m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
			m_ViewProjMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

		void RecalculateProjectionMatrix()
		{
			m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
			m_ViewProjMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

	private:
		// Projection settings
		float m_FOV;
		float m_AspectRatio;
		float m_NearClip;
		float m_FarClip;

		// Camera position and orientation
		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;

		float m_Yaw;
		float m_Pitch;

		// Matrices
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjMatrix;
	};

}
