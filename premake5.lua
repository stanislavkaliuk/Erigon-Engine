workspace "ErigonEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["ImGui"] = "ErigonEngine/vendor/imgui"
IncludeDir["SDL"] = "ErigonEngine/vendor/SDL/include"

include "ErigonEngine/vendor/imgui"

project "ErigonEngine"
	location "ErigonEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "eepch.h"
	pchsource "ErigonEngine/src/eepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
	 	"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.SDL}"
	}

	links
	{
		"ImGui",
		"SDL2.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ERIGON_WINDOWS",
			"ERIGON_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "EE_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "EE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "EE_DIST"
		runtime "Release"
		optimize "On"
	
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"ErigonEngine/vendor/spdlog/include",
		"ErigonEngine/vendor/SDL/include",
		"ErigonEngine/src",
		"ErigonEngine/vendor"
	}

	links
	{
		"ErigonEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ERIGON_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EE_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "EE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "EE_DIST"
		runtime "Release"
		optimize "On"