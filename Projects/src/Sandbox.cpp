#include <Nitrogen.h>

#include <iostream>

class Sandbox : public Nitrogen::Application
{

};

Nitrogen::Application* Nitrogen::CreateApplication()
{
	return new Sandbox();
}