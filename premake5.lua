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
    return queryTerminal("python -c \"import sys; import os; import glob; path = os.path.dirname(os.path.dirname(sys.executable)); libs = glob.glob(path + '/lib/python3.7'); print(os.path.splitext(os.path.basename(libs[-1]))[0]);\"")
end

pythonPath      = getPythonPath()
pythonIncludePath = pythonPath .. "/../include/python3.7"
pythonLibPath     = pythonPath .. "/../lib"
pythonLib         = getPythonLib()

if pythonPath == "" then
    error("Failed to find python path!")
elseif pythonLib == "" then
    error("Failed to find python libary!")
else
	print("Python path: " .. pythonPath)
    print("Python includes: " .. pythonIncludePath)
    print("Python libs: " .. pythonLibPath)
    print("lib: " .. pythonLib)
end

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
include "sandbox"
include "demo1"