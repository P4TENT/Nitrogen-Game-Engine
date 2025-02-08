#include "GameLayer.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GameLayer::GameLayer()
	: Layer("GameLayer")
{
}

void GameLayer::OnAttach()
{
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Nitrogen::Timestep ts)
{
}

void GameLayer::OnImGuiRender()
{
}

void GameLayer::OnEvent(Nitrogen::Event& e)
{
}
