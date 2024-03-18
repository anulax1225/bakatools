project "bakatools"
	kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

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
    }

    filter "system:windows"
        defines
        {
            "BK_PLAFORM_WINDOWS"
        }
    
    filter "system:linux"
        defines
        {
            "BK_PLAFORM_LINUX"
        }
    
    filter "configurations:Debug"
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
