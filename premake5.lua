workspace "Nitrogen"
	architecture "x64"
	buildoptions {"/utf-8"}
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Nitrogen/vendor/GLFW/include"
IncludeDir["Glad"] = "Nitrogen/vendor/Glad/include"
IncludeDir["ImGui"] = "Nitrogen/vendor/imgui"
IncludeDir["glm"] = "Nitrogen/vendor/glm"
IncludeDir["stb_image"] = "Nitrogen/vendor/stb_image"

include "Nitrogen/vendor/GLFW"
include "Nitrogen/vendor/Glad"
include "Nitrogen/vendor/imgui"

project "Nitrogen"
	location "Nitrogen"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ntgpch.h"
	pchsource "Nitrogen/src/ntgpch.cpp"
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}
	links 
	{
		"GLFW", 
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"NTG_PLATFORM_WINDOWS",
			"NTG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
	filter "configurations:Debug"
		defines "NTG_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "NTG_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "NTG_DIST"
		runtime "Release"
		optimize "on"

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
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Nitrogen/vendor/spdlog/include",
		"Nitrogen/vendor/imgui",
		"Nitrogen/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Nitrogen"
	}

	filter "system:windows"
		staticruntime "On"  
		systemversion "latest"

		defines
		{
			"NTG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NTG_DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "NTG_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines "NTG_DIST"
		runtime "Release"
		optimize "on"
