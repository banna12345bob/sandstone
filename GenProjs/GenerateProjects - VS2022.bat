@echo off
pushd ..
call vendor\bin\premake\premake5_windows.exe vs2022
popd
PAUSE
