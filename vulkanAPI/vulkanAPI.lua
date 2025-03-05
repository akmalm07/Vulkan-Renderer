project "VulkanAPI"
    location "VulkanAPI"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    -- Include directories
    includedirs 
    {
        "%{IncludeDir.Vulkan}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.JSON}",
        "global",            
        "include",           
        "vulkan",
        "src",
    }

    -- Files
    files 
    {
        "src/**.cpp",           
        "vulkan/tools/src/**.cpp", 
        "vulkan/vkInit/src/**.cpp",
        "vulkan/vkUtil/src/**.cpp", 
        "include/**.h",           
        "vulkan/tools/include/**.h", 
        "vulkan/vkInit/include/**.h",
        "vulkan/vkUtil/include/**.h", 
        "vulkan/tools/include/**.inl", 
        "vulkan/vkInit/include/**.inl",
        "vulkan/vkUtil/include/**.inl",
        "global/**.h",
    }

    -- Library directories
    libdirs 
    { 
        "%{LibDir.Vulkan}",
        "%{LibDir.GLFW}"
    }

    -- Links
    links 
    { 
        "glfw3.lib",
        "vulkan-1.lib"
    }

    -- Toolset and compiler settings
    filter "toolset:msc"
        buildoptions { "/std:c++23" }

    filter "toolset:gcc or toolset:clang"
        buildoptions { "-std=c++23" }

    -- Configuration settings
    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"
        optimize "Off"

    filter "configurations:Release"
        symbols "Off"
        optimize "On"
        defines "NDEBUG"

    -- Windows system settings
    filter "system:windows"
        systemversion "latest"
        defines "PLATFORM_WINDOWS"
    
    -- Visual Studio specific settings
    filter "action:vs*"
        defines "_CRT_SECURE_NO_WARNINGS"
        buildoptions { "/std:c++23" }
        staticruntime "on"

    -- Linux and GCC/Clang settings
    filter "system:linux or toolset:gcc or toolset:clang"
        buildoptions { "-include pch.h" }