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
    p = string.gsub(p, "\\\\", "\\") -- replace double backslash
    p = string.gsub(p, "\\", "/") -- flip slashes
    return p
end

function getPythonLib()
    return queryTerminal("python -c \"import sys; import os; import glob; path = os.path.dirname(sys.executable); libs = glob.glob(path + '/libs/python*'); print(os.path.splitext(os.path.basename(libs[-1]))[0]);\"")
end

print(os.host())
if os.host() == "windows" then
    pythonPath      = getPythonPath()
    pythonIncludePath = pythonPath .. "/../include/*"
    pythonLibPath     = pythonPath .. "/../lib/"
    -- pythonIncludePath = pythonPath .. "/include/"
    -- pythonLibPath     = pythonPath .. "/libs/"
    pythonLib         = getPythonLib()
elseif os.host() == "macosx" then
    pythonPath        = getPythonPath()
    pythonIncludePath = pythonPath .. "/../include/*"
    pythonLibPath     = pythonPath .. "/../lib/"
    pythonLib         = pythonLibPath .. "/libpython3.11.dylib"
else
    pythonPath        = ""
    pythonIncludePath = ""
    pythonLibPath     = ""
    pythonLib         = ""
end

if (pythonPath == "" or pythonLib == "") and os.get() == "windows" then
    error("Failed to find python path!")
else
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