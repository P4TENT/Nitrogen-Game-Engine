#pragma once

// |================================================================|
// |																|
// |						█▀▀ █▀█ █▀█ █▀▀						|
// |						█▄▄ █▄█ █▀▄ ██▄						|
// |                              									|
// |================================================================|
// | Includes:														|
// |  - Core/CoreApp.h												|
// |  - Core/Timestep.h												|
// |  - Core/Log.h													|
// |  - Core/EntryPoint.h											|
// |  - Core/Layer.h												|
// |  - Core/LayerStack.h											|
// |  - Core/Input/Input.h											|
// |  - Core/Input/KeyCodes.h										|
// |  - Core/Input/MouseButtonCodes.h								|
// |  - Core/Events/Event.h											|
// |  - Core/Events/AppEvent.h										|
// |  - Core/Events/KeyEvent.h										|
// |  - Core/Events/MouseEvent.h									|
// |  - Core/ImGui/ImGuiLayer.h										|
// |================================================================|
#include "Nitrogen/Core/CoreApp.h"
#include "Nitrogen/Core/Timestep.h"
#include "Nitrogen/Core/Log.h"
// |================================================================|
// | Entry Point													|
// |================================================================|
#include "Nitrogen/Core/EntryPoint.h"
// |================================================================|
// | Layer Stack												    |
// |================================================================|
#include "Nitrogen/Core/Layer.h"
#include "Nitrogen/Core/LayerStack.h"
// |================================================================|
// | Input															|
// |================================================================|
#include "Nitrogen/Core/Input/Input.h"
#include "Nitrogen/Core/Input/KeyCodes.h"
#include "Nitrogen/Core/Input/MouseButtonCodes.h"
// |================================================================|
// | Events															|
// |================================================================|
#include "Nitrogen/Core/Events/Event.h"
#include "Nitrogen/Core/Events/AppEvent.h"
#include "Nitrogen/Core/Events/KeyEvent.h"
#include "Nitrogen/Core/Events/MouseEvent.h"
// |================================================================|
// | ImGui															|
// |================================================================|
#include "Nitrogen/ImGui/ImGuiLayer.h"


// |================================================================|
// |																|
// |			█▀█ █▀▀ █▄░█ █▀▄ █▀▀ █▀█ █▀▀ █▀█				|
// |			█▀▄ ██▄ █░▀█ █▄▀ ██▄ █▀▄ ██▄ █▀▄				|
// |																|
// |================================================================|
// | * Includes:													|
// |	- Renderer/GraphicsContext.h                                |
// |	- Renderer/Renderer.h		                                |
// |	- Renderer/RendererCommand.h		                        |
// |	- Renderer/Renderer2D.h										|
// |	- Renderer/Shader.h									        |
// |	- Renderer/Buffer.h									        |
// |	- Renderer/VertexArray.h									|
// |	- Renderer/OrthographicCamera.h								|
// |	- Renderer/OrthographicCameraController.h					|
// |	- Renderer/Texture.h										|
// |================================================================|
#include "Nitrogen/Renderer/GraphicsContext.h"
#include "Nitrogen/Renderer/Renderer.h"
#include "Nitrogen/Renderer/RendererCommand.h"
#include "Nitrogen/Renderer/Renderer2D.h"
// |================================================================|
// | Shaders & Buffers												|
// |================================================================|
#include "Nitrogen/Renderer/Shader.h"
#include "Nitrogen/Renderer/Buffer.h"
#include "Nitrogen/Renderer/VertexArray.h"
// |================================================================|
// | Orthographic Camera											|
// |================================================================|
#include "Nitrogen/Renderer/OrthographicCamera.h"
#include "Nitrogen/Renderer/OrthographicCameraController.h"
// |================================================================|
// | Texutre														|
// |================================================================|
#include "Nitrogen/Renderer/Texture.h"