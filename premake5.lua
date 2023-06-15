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

project "sandstone"
	location "sandstone"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("compile/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("compile/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines{
		
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		systemversion "latest"

	filter "system:macosx"
		systemversion "latest"
        xcodebuildsettings { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

	filter "configurations:Debug"
		defines "SU_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SU_RELEASE"
		runtime "Release"
		symbols "off"
		optimize "on"

	filter "configurations:Dist"
		defines "SU_DIST"
		runtime "Release"
		symbols "off"
		optimize "on"

project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("compile/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("compile/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/**.json"
	}

	includedirs
	{
		"sandstone/vendor/spdlog/include",
		"sandstone/src",
		"sandstone/vendor"
	}

	links
	{
		"sandstone"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		systemversion "latest"

	filter "system:macosx"
		systemversion "latest"
        xcodebuildsettings { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

	filter "configurations:Debug"
		defines "SU_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SU_RELEASE"
		runtime "Release"
		symbols "off"
		optimize "on"

	filter "configurations:Dist"
		defines "SU_DIST"
		runtime "Release"
		optimize "on"
		symbols "off"
