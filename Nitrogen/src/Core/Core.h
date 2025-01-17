#pragma once

#ifdef NTG_PLATFORM_WINDOWS

#include <memory>

#include "Log.h"

#define BIT(x) (1 << x)

#ifdef NTG_ENABLE_ASSERTS
	#define NTG_ASSERT(x, ...) { if(!(x)) { NTG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NTG_CORE_ASSERT(x, assertCode, ...) { if(!(x)) { NTG_CORE_ERROR("Assertion Failed (code: {0}): {1}", ((assertCode != 0) ? assertCode : 2147483648), __VA_ARGS__); __debugbreak(); } }
#else
	#define NTG_ASSERT(x, ...)
	#define NTG_CORE_ASSERT(x, ...)
#endif

namespace Nitrogen {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args&&... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename... Args>
	constexpr Scope<T> CreateRef(Args&&... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
}
}

#else
	#error Nitrogen Currently Supports Olny The Windows Operating System!
#endif