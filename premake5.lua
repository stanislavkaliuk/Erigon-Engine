workspace "ErigonEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ErigonEngine"
	location "ErigonEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ERIGON_WINDOWS",
			"ERIGON_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	filter "configurations:Debug"
		defines "EE_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "EE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EE_DIST"
		optimize "On"
	
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"ErigonEngine/vendor/spdlog/include",
		"ErigonEngine/src"
	}

	links
	{
		"ErigonEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ERIGON_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EE_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "EE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EE_DIST"
		optimize "On"