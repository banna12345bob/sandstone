project "lua"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("%{wks.location}/compile/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/compile/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.c"
	}

	includedirs
	{
		"src"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		systemversion "latest"

	filter "system:macosx"
		systemversion "latest"
        xcodebuildsettings { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

	filter "configurations:Debug*"
		defines "SS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release*"
		defines "SS_RELEASE"
		runtime "Debug"
		symbols "on"

	filter "configurations:Dist*"
		defines "SS_DIST"
		runtime "Release"
		symbols "off"
		optimize "on"
