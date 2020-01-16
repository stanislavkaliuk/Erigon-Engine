project "EECS"
    kind "StaticLib"
    language "C++"
    staticruntime "On"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/".. outputdir .. "/%{prj.name}")

    files
    {
        "include/*.h",
        "src/*.cpp"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        
    filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "On"