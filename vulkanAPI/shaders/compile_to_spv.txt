@echo off
setlocal enabledelayedexpansion

:: Set the path to Vulkan's glslc compiler
set GLSLC="%VULKAN_SDK%\Bin\glslc.exe"

:: Ensure the compiler exists
if not exist %GLSLC% (
    echo Error: Vulkan glslc compiler not found. Check your VULKAN_SDK path.
    exit /b 1
)

:: Create the spv directory if it doesn't exist
if not exist spv mkdir spv

:: Iterate over all .vert and .frag shader files in the directory
for %%f in (*.vert *.frag) do (
    set "INPUT_FILE=%%f"
    set "OUTPUT_FILE=spv\%%~nf.spv"

    echo Compiling !INPUT_FILE!...
    %GLSLC% !INPUT_FILE! -o !OUTPUT_FILE!

    if !errorlevel! neq 0 (
        echo Compilation failed for !INPUT_FILE!
        exit /b !errorlevel!
    )
)

echo All shaders compiled successfully.
exit /b 0