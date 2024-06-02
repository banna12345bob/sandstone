project "sandstone"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/compile/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/compile/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"vendor/json/include",
		"vendor/lua/src"
	}

	links
	{
		"lua"
	}

	filter "system:windows"
		systemversion "latest"
		postbuildcommands {
			"{COPY} %{wks.location}/%{prj.name}/version.json %{cfg.targetdir}",
			"{COPYDIR} %{wks.location}/%{prj.name}/../data/ %{cfg.targetdir}/../data/"
		}

	filter "system:linux"
		systemversion "latest"
		postbuildcommands {
			"{COPY} %{wks.location}/%{prj.name}/version.json %{cfg.targetdir}",
			"{COPYDIR} %{wks.location}/%{prj.name}/../data/ %{cfg.targetdir}/../"
		}

	filter "system:macosx"
		systemversion "latest"
        xcodebuildsettings { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }
		postbuildcommands {
			"{COPY} %{wks.location}/%{prj.name}/version.json %{cfg.targetdir}",
			"{COPYDIR} %{wks.location}/%{prj.name}/../data/ %{cfg.targetdir}/../"
		}

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
