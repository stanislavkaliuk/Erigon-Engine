project "EECS"
    kind "StaticLib"
    language "C++"
    staticruntime "On"
    cppdialect "C++17"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/".. outputdir .. "/%{prj.name}")

    files
    {
        "src/*.hpp"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
