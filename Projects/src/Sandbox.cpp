#include <Nitrogen.h>

#include <iostream>

class BasicLayer : public Nitrogen::Layer
{
public:
	BasicLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		NTG_CORE_INFO("ExampleLayer::Update");
	}

	void OnEvent(Nitrogen::Event& event) override
	{
		//NTG_CORE_TRACE("{0}", event.ToString());
	}
};

class Sandbox : public Nitrogen::Application
{
public:
	Sandbox()
	{
		PushLayer(new BasicLayer());
	}

	~Sandbox()
	{

	}
};

Nitrogen::Application* Nitrogen::CreateApplication()
{
	return new Sandbox();
}