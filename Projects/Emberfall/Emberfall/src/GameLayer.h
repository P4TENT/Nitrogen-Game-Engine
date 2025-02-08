#pragma once

#include "Nitrogen.h"

class GameLayer : public Nitrogen::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Nitrogen::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Nitrogen::Event& e) override;
};