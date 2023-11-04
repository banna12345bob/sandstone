project "sandbox"
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
		"**.json",
		"**.py"
	}

	includedirs
	{
		"%{wks.location}/sandstone/vendor/spdlog/include",
		"%{wks.location}/sandstone/vendor/json/include",
		"%{wks.location}/sandstone/src",
		"%{wks.location}/sandstone/vendor"
	}

	links
	{
		"sandstone"
	}

	postbuildcommands {
		"{COPY} %{wks.location}/%{prj.name}/%{prj.name}Objects.json %{cfg.targetdir}",
		"{COPY} %{wks.location}/%{prj.name}/%{prj.name}Rooms.json %{cfg.targetdir}",
		"{COPY} " .. pythonPath .. "/".. pythonLib .. ".dll %{cfg.targetdir}",
		"{COPY} %{wks.location}/%{prj.name}/scripts/* %{cfg.targetdir}/scripts/"
	}

	filter "system:windows"
		systemversion "latest"
		defines "SS_PY_SCRIPTING"

		libdirs {
			pythonLibPath
		}
	
		links {
			pythonLib
		}

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
		optimize "on"
		symbols "off"
