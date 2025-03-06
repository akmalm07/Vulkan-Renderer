project "VulkanAPI"
    location "VulkanAPI"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
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
        "global/**.cpp"
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
        "glfw3_mt.lib",
        "vulkan-1.lib",
        "libcmt.lib",
        "kernel32.lib"
    }

    pchheader "headers.h"
    pchsource "headers.cpp"

    flags { "Verbose" }


    -- Toolset and compiler settings
    filter "toolset:msc"
        toolset "msc-v143" --
        buildoptions { "/std:c++23" } 
        
    filter "toolset:gcc or toolset:clang"
        buildoptions { "-std=c++23" }

    -- Configuration settings
    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"
        optimize "Off"
        runtime "Release"  

    filter "configurations:Release"
        symbols "Off"
        optimize "On"
        defines "NDEBUG"
        runtime "Release"  

    -- Windows system settings
    filter "system:windows"
        systemversion "latest"
        defines "PLATFORM_WINDOWS"
    
    -- Visual Studio specific settings
    filter "action:vs*"
        defines "_CRT_SECURE_NO_WARNINGS"
        staticruntime "on"

    -- Linux and GCC/Clang settings
    filter "system:linux or toolset:gcc or toolset:clang"
        buildoptions { "-include pch.h" }
    
    filter "files:global/headers.cpp"   
        buildoptions { "/Ycheaders.h" }
    