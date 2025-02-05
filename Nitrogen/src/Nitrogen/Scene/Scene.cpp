#include "ntgpch.h"
#include "Scene.h"

#include "Components.h"

#include "glm/glm.hpp"

#include "Nitrogen/Renderer/Renderer2D.h"

#include "Entity.h"

#include <string.h>

namespace Nitrogen {

	static void DoMath(const glm::mat4& transform)
	{

	}

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity e{ m_Registry.create(), this };
		e.AddComponent<TransformComponent>();
		auto& tag = e.AddComponent<TagComponent>(name);
		tag.Tag = (name.empty()) ? "Entity..." : name;

		return e;
	}

	void Scene::OnUpdate(Timestep ts)
	{
	}

}