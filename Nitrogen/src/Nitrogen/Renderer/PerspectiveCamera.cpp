#include "ntgpch.h"
#include "PerspectiveCamera.h"

namespace Nitrogen {

	void PerspectiveCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}
	
	
	void PerspectiveCamera::SetRotation(float yaw, float pitch)
	{
		m_Yaw = yaw;
		m_Pitch = glm::clamp(pitch, -89.0f, 89.0f); // Prevent gimbal lock
		RecalculateViewMatrix();
	}
	
	
	void PerspectiveCamera::SetProjection(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_FOV = fov;
		m_AspectRatio = aspectRatio;
		m_NearClip = nearClip;
		m_FarClip = farClip;
		RecalculateProjectionMatrix();
	}

}
