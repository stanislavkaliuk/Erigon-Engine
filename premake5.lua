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
IncludeDir["GLFW"] = "ErigonEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "ErigonEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "ErigonEngine/vendor/imgui"
IncludeDir["Glm"] = "ErigonEngine/vendor/glm"
IncludeDir["stb_image"] = "ErigonEngine/vendor/stb_image"
IncludeDir["EECS"] = "ErigonEngine/vendor/EECS/src"
IncludeDir["DragonBones"] = "ErigonEngine/vendor/DragonBones"
IncludeDir["YAML"] = "ErigonEngine/vendor/yamlcpp/include"

include "ErigonEngine/vendor/GLFW"
include "ErigonEngine/vendor/Glad"
include "ErigonEngine/vendor/imgui"
include "ErigonEngine/vendor/EECS"
include "ErigonEngine/vendor/DragonBones"

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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
	 	"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.YAML}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.Glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.EECS}",
		"%{IncludeDir.DragonBones}",
	}

	libdirs
	{
		"%{prj.name}/vendor/yamlcpp/lib",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"yaml-cppd.lib",
		"EECS",
		"DragonBones"
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
		"Sandbox/src",
		"ErigonEngine/vendor/spdlog/include",
		"ErigonEngine/src",
		"ErigonEngine/vendor",
		"%{IncludeDir.Glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.EECS}",
		"%{IncludeDir.YAML}"
	}

	links
	{
		"ErigonEngine"
	}

	filter "system:windows"
		systemversion "latest"

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
