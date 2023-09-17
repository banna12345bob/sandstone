function queryTerminal(command)
    local success, handle = pcall(io.popen, command)
    if not success then 
        return ""
    end

    result = handle:read("*a")
    handle:close()
    result = string.gsub(result, "\n$", "") -- remove trailing whitespace
    return result
end

function getPythonPath()
    local p = queryTerminal('python -c "import sys; import os; print(os.path.dirname(sys.executable))"')
    
    -- sanitize path before returning it
    p = string.gsub(p, "\\", "\\") -- replace double backslash
    p = string.gsub(p, "\\", "/") -- flip slashes
    return p
end

function getPythonLib()
    return queryTerminal("python -c \"import sys; import os; import glob; path = os.path.dirname(os.path.dirname(sys.executable)); libs = glob.glob(path + '/lib/python3.11'); print(os.path.splitext(os.path.basename(libs[-1]))[0]);\"")
end

pythonPath      = getPythonPath()
pythonIncludePath = pythonPath .. "/../include/python3.11/"
pythonLibPath     = pythonPath .. "/../libs/python3.11/"
pythonLib         = getPythonLib()

if pythonPath == "" then
    error("Failed to find python path!")
elseif pythonLib == "" then
    error("Failed to find python libary!")
else
    print("Python includes: " .. pythonIncludePath)
    print("Python libs: " .. pythonLibPath)
    print("lib: " .. pythonLib)
end

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

	defines{
		
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"vendor/json/include",
		"vendor/pybind11/include",
		pythonIncludePath
	}

	postbuildcommands {
		"{COPY} %{wks.location}/%{prj.name}/version.json %{cfg.targetdir}"
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
