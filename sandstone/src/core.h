#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define SS_PLATFORM_WINDOWS
	#else
		#error "Unsupported Windows platform"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
		#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS Sim not supported"
	#elif TARGET_OS_IPHONE == 1
		#define SS_PLATFORM_IOS
		#error "Sandstone doesn't support IOS"
	#elif TARGET_OS_MAC == 1
        #define SS_PLATFORM_MACOS
        #if TARGET_CPU_ARM64
            #define SS_PLATFORM_MACOS_ARM64
        #elif TARGET_CPU_X86_64
            #define SS_PLATFORM_MACOS_x86
        #else
            #error "Unknown Mac architecture!"
        #endif
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define SS_PLATFORM_ANDROID
	#error "Sandstone doesn't support Android"
#elif defined(__linux__)
	#define SS_PLATFORM_LINUX
	#error "Sandstone doesn't support Linux"
#else
	#error "What kind of platform are you using? What ever it is it's not supported"
#endif

#ifdef SS_DEBUG
    #if defined(SS_PLATFORM_WINDOWS)
        #define SS_DEBUGBREAK() __debugbreak()
    #elif defined(SS_PLATFORM_LINUX)
        #include <signal.h>
        #define SS_DEBUGBREAK() raise(SIGTRAP)
    #elif defined(SS_PLATFORM_MACOS_x86)
        #define SS_DEBUGBREAK() __asm__ volatile("int $0x03")
    #elif defined(SS_PLATFORM_MACOS_ARM64)
        #define SS_DEBUGBREAK()
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
        #define SS_ENABLE_ASSERTS
    #else
    #define SS_DEBUGBREAK()
#endif

#ifdef SS_ENABLE_ASSERTS
#define SS_ASSERT(x, ...) { if(!(x)) { SS_ERROR("Assertion Failed: {0}", __VA_ARGS__); SS_DEBUGBREAK(); } }
#define SS_CORE_ASSERT(x, ...) { if(!(x)) { SS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); SS_DEBUGBREAK(); } }
#else
#define SS_ASSERT(x, ...)
#define SS_CORE_ASSERT(x, ...)
#endif

