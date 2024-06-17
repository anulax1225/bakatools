project "bakatools"
	kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    systemversion "latest"
    staticruntime "on"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "bakatoolspch.h"
    pchsource "bakatoolspch.cpp"

    includedirs 
    {
        "%{IncludeDirs.spdlog}",
        "%{IncludeDirs.bakatools}"
    }

    files 
    {
        "%{prj.location}/src/bakatools/**.h",
        "%{prj.location}/src/bakatools/**.cpp",
        "%{prj.location}/src/bakatoolspch.h",
        "%{prj.location}/src/bakatoolspch.cpp",
    }

    filter "system:windows"
        buildoptions "/MT"
        defines
        {
            "BK_PLATFORM_WINDOWS"
        }
    
    filter "system:linux"
        defines
        {
            "BK_PLATFORM_LINUX"
        }
        
    
    filter "configurations:Debug"
        --buildoptions { "-Wall", "-Wextra" }
        defines 
        { 
            "BK_DEBUG",
            "DEBUG"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines 
        { 
            "BK_RELEASE",
            "NDEBUG"
        }
        runtime "Release"
        optimize "on"
