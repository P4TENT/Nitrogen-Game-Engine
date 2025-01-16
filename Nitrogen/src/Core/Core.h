#pragma once

#ifdef NTG_PLATFORM_WINDOWS

#include <memory>

#define BIT(x) (1 << x)

#ifdef NTG_ENABLE_ASSERTS
	#define NTG_ASSERT(x, ...) { if(!(x)) { NTG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NTG_CORE_ASSERT(x, ...) { if(!(x)) { NTG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define NTG_ASSERT(x, ...)
	#define NTG_CORE_ASSERT(x, ...)
#endif

namespace Nitrogen {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}

#else
	#error Nitrogen Currently Supports Olny The Windows Operating System!
#endif