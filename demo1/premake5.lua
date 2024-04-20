project "demo1"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/compile/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/compile/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"**.json"
	}

	includedirs
	{
		"%{wks.location}/sandstone/vendor/spdlog/include",
		"%{wks.location}/sandstone/vendor/json/include",
		"%{wks.location}/sandstone/vendor/lua/src",
		"%{wks.location}/sandstone/src"
	}

	links
	{
		"sandstone"
	}

	postbuildcommands {
		"{COPY} %{wks.location}/%{prj.name}/%{prj.name}Objects.json %{cfg.targetdir}",
		"{COPY} %{wks.location}/%{prj.name}/%{prj.name}Rooms.json %{cfg.targetdir}"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		systemversion "latest"
		links {"lua"}

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
		optimize "on"
		symbols "off"
