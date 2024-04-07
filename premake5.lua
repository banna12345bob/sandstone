workspace "sandstone"
	startproject "sandbox"

	configurations
	{
		"Debug_x86_64",
		"Release_x86_64",
		"Dist_x86_64",
		"Debug_ARM64",
		"Release_ARM64",
		"Dist_ARM64",
	}
	filter "configurations:*_ARM64"
		architecture "ARM64"
	filter "configurations:*_x86_64"
		architecture "x86_64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "sandstone"
include "consoleSandbox"
include "demo1"
include "sandstone/vendor/lua"