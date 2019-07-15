#pragma once

#ifdef ERIGON_WINDOWS
	#if EE_DLL_LINK
		#ifdef ERIGON_DLL
		#define ERIGON_API __declspec(dllexport)
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