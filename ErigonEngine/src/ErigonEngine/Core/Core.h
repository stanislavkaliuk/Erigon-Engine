#pragma once
#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define ERIGON_WINDOWS
	#else
		#error "x86 platform not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define HZ_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define HZ_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple Platform!"
	#endif
#elif defined(__ANDROID__)
	#define ERIGON_ANDROID
	#error "Android currently not supported!"
#elif defined(__linux__)
	#define ERIGON_LINUX
	#error "Linux currently not supported!"
#endif


#ifdef ERIGON_WINDOWS
	#if EE_DLL_LINK
		#ifdef ERIGON_DLL
		#define ERIGON_API __declspec(dllexp ort)
		#else // ERIGON_DLL
		#define ERIGON_API __declspec(dllimport)
		#endif
	#else
		#define ERIGON_API
	#endif
#else
#error Erigon Engine supports Windows only
#endif // ERIGON_WINDOWS

#ifdef EE_DEBUG
	#define EE_ENABLE_ASSERTS
#endif

#ifdef EE_ENABLE_ASSERTS

#define EE_ASSERT(x,...){if(!(x)) {EE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#define EE_CORE_ASSERT(x,...){if(!(x)) {EE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	
#else

#define EE_ASSERT(x,...)
#define EE_CORE_ASSERT(x,...)

#endif


#define BIT(x) (1<<x)

#define EE_BIND_EVENT(fn) std::bind(&fn,this,std::placeholders::_1)

namespace ErigonEngine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward < Args(args)...);
	}
}