#pragma once

#include <glm/glm.hpp>
#include <string.h>
#include "Nitrogen/Scene/Components.h"
#include "Nitrogen/Renderer/Texture.h"

namespace Nitrogen {

	struct TransformComponent {
		glm::mat4 Transform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform) : Transform(transform) {}

		operator const glm::mat4& () const { return Transform; }
		operator glm::mat4& () { return Transform; }
	};


	struct ColorComponent {
		glm::vec4 Color = glm::vec4(1.0f);

		ColorComponent() = default;
		ColorComponent(const ColorComponent&) = default;
		ColorComponent(const glm::vec4& color) : Color(color) {}
	};	
	
	
	struct TagComponent {
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) : Tag(tag) {}
	};


	struct Texture2DComponent {
		Ref<Texture2D> Texture;
 
		Texture2DComponent() = default;
		Texture2DComponent(const Texture2DComponent&) = default;
		Texture2DComponent(const Ref<Texture2D> texture) : Texture(texture) {}
	};

}