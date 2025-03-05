workspace "Vulkan Renderer"
    architecture "x64"
    startproject "VulkanAPI"

    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "../vendor/GLFW/include"
IncludeDir["GLM"] = "../vendor/GLM"
IncludeDir["Vulkan"] = "%VULKAN_SDK%/Include"
IncludeDir["JSON"] = "../vendor/JSON"

LibDir = {}
LibDir["Vulkan"] = "%VULKAN_SDK%/Lib"
LibDir["GLFW"] = "../vendor/GLFW/lib"


group "vulkanAPI"
    include "vulkanAPI/vulkanAPI.lua"