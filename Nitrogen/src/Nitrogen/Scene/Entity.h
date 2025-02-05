#pragma once

#include "Scene.h"

#include "Nitrogen/Core/Core.h"

namespace Nitrogen {

	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity entity, Scene* scene) : m_EntityHandle(entity), m_Scene(scene) {}
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			NTG_CORE_ASSERT(!HasComponent<T>(), "Entity already has Component!");

			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			NTG_CORE_ASSERT(HasComponent<T>(), "Entity does not have Component!");

			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			NTG_CORE_ASSERT(HasComponent<T>(), "Entity does not have Component!");

			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return (uint32_t)m_EntityHandle != 0; }
		
	private:
		entt::entity m_EntityHandle{ 0 };
		Scene* m_Scene = nullptr;
	};

}