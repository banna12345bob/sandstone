-- This sucks but you've gotta do what you've gotta do
dofile("scripts/bobrick.lua")
dofile("scripts/rickbob.lua")

function MyLuaFunction()
    Trace("This is logged by lua")
    Info("Info logged by lua")
    Warn("Warning logged by lua")
    Error("Error logged by lua")
    Fatal("Fatal logged by lua")
end