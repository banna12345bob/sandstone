workspace "sandstone"
	architecture "x86_64"
	startproject "sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "sandstone"
include "sandbox"
include "demo1"