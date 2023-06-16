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
