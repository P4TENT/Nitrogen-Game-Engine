#pragma once

#include <memory>

#define NTGINT int
#define NTGUINT unsigned int
#define NTGUBYTE unsigned char

#define NTG_ENABLE_ASSERTS

#ifdef NTG_PLATFORM_WINDOWS

#if NTG_DYNAMIC_LINK
	#ifdef NTG_BUILD_DLL
		#define NITRO_API __declspec(dllexport)
	#else 
		#define NITRO_API __declspec(dllimport)
	#endif
#else
	#define NITRO_API
#endif

#else 
	#error Nitro only supports Windows!!
#endif

#ifdef NTG_ENABLE_ASSERTS
	#define NTG_ASSERT(x, ...) { if(!(x)) { NTG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NTG_CORE_ASSERT(x, ...) { if(!(x)) { NTG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define NTG_ASSERT(x, ...)
	#define NTG_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define NTG_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Nitrogen{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref	= std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}