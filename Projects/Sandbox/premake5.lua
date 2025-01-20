-- Sandbox 															 
																		
workspace "Sandbox" 												
	configurations { "Debug", "Release", "Dist" } 						
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 	
	buildoptions {"/utf-8"} 											
	architecture "x64" 													
 																		
	IncludeDir = {} 													
	IncludeDir["glm"] = "../../Nitrogen/vendor/glm" 					
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
        "../../Nitrogen/vendor/spdlog/include", 						
        "../../Nitrogen/vendor/imgui", 								
        "../../Nitrogen/src", 											
        "%{IncludeDir.glm}" 											
    } 																	
 																		
	libdirs 															
	{ 																	
	"$(SolutionDir)/backend/lib" 										
	} 																	
 																		
    links 																
    { 																	
		"Nitrogen", 													
		"GLFW", 														
	"Glad",															
	"ImGui",														
	"opengl32.lib"													
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
