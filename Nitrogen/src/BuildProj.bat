@echo off

:: Navigate to the "Projects" folder
cd ..
:: Nitrogen Dir Path
set EnginePath=%cd%
cd ..
cd Projects

:: Prompt the user to enter a project name
set /p ProjName="Enter Project Name: "

:: Create the project folder and subdirectories
mkdir "%ProjName%"
cd "%ProjName%"
set ProjectPath=%cd%

mkdir backend
mkdir backend\lib
mkdir backend\scripts

cd %ProjectPath%

:: Create the premake5.lua file
echo -- %ProjName% 															 > premake5.lua
echo.																		>> premake5.lua
echo workspace "%ProjName%" 												>> premake5.lua
echo 	configurations { "Debug", "Release", "Dist" } 						>> premake5.lua
echo 	outputdir = "%%{cfg.buildcfg}-%%{cfg.system}-%%{cfg.architecture}" 	>> premake5.lua
echo 	buildoptions {"/utf-8"} 											>> premake5.lua
echo 	architecture "x64" 													>> premake5.lua
echo. 																		>> premake5.lua
echo 	IncludeDir = {} 													>> premake5.lua
echo 	IncludeDir["glm"] = "../../Nitrogen/vendor/glm" 					>> premake5.lua
echo project "%ProjName%" 													>> premake5.lua
echo     location "%ProjName%" 												>> premake5.lua
echo     kind "ConsoleApp" 													>> premake5.lua
echo     language "C++" 													>> premake5.lua
echo     cppdialect "C++17" 												>> premake5.lua
echo     staticruntime "on" 												>> premake5.lua
echo. 																		>> premake5.lua
echo     targetdir ("bin/" .. outputdir .. "/%%{prj.name}") 				>> premake5.lua
echo     objdir ("bin-int/" .. outputdir .. "/%%{prj.name}") 				>> premake5.lua
echo. 																		>> premake5.lua
echo     files 																>> premake5.lua
echo     { 																	>> premake5.lua
echo         "%%{prj.name}/src/**.h", 										>> premake5.lua
echo         "%%{prj.name}/src/**.cpp" 										>> premake5.lua
echo     } 																	>> premake5.lua
echo. 																		>> premake5.lua
echo     includedirs 														>> premake5.lua
echo     { 																	>> premake5.lua
echo         "../../Nitrogen/vendor/spdlog/include", 						>> premake5.lua
echo         "../../Nitrogen/vendor/imgui", 								>> premake5.lua
echo         "../../Nitrogen/src", 											>> premake5.lua
echo         "%%{IncludeDir.glm}" 											>> premake5.lua
echo     } 																	>> premake5.lua
echo. 																		>> premake5.lua
echo 	libdirs 															>> premake5.lua
echo 	{ 																	>> premake5.lua
echo 	"$(SolutionDir)/backend/lib" 										>> premake5.lua
echo 	} 																	>> premake5.lua
echo. 																		>> premake5.lua
echo     links 																>> premake5.lua
echo     { 																	>> premake5.lua
echo 		"Nitrogen", 													>> premake5.lua
echo 		"GLFW", 														>> premake5.lua
echo		"Glad",															>> premake5.lua
echo		"ImGui",														>> premake5.lua
echo		"opengl32.lib"													>> premake5.lua
echo     } 																	>> premake5.lua
echo. 																		>> premake5.lua
echo     filter "system:windows" 											>> premake5.lua
echo         staticruntime "On" 											>> premake5.lua
echo         systemversion "latest" 										>> premake5.lua
echo. 																		>> premake5.lua
echo         defines 														>> premake5.lua
echo         { 																>> premake5.lua
echo             "NTG_PLATFORM_WINDOWS" 									>> premake5.lua
echo         } 																>> premake5.lua
echo. 																		>> premake5.lua
echo     filter "configurations:Debug" 										>> premake5.lua
echo         defines "NTG_DEBUG" 											>> premake5.lua
echo         runtime "Debug" 												>> premake5.lua
echo         symbols "on" 													>> premake5.lua
echo. 																		>> premake5.lua
echo     filter "configurations:Release" 									>> premake5.lua
echo         defines "NTG_RELEASE" 											>> premake5.lua
echo         runtime "Release" 												>> premake5.lua
echo         optimize "on" 													>> premake5.lua
echo. 																		>> premake5.lua
echo     filter "configurations:Dist" 										>> premake5.lua
echo         defines "NTG_DIST" 											>> premake5.lua
echo         runtime "Release" 												>> premake5.lua
echo         optimize "on" 													>> premake5.lua

call ..\..\vendor\bin\premake\premake5.exe vs2022

cd %ProjName%
mkdir src
mkdir src\assets

copy "%EnginePath%\..\bin\Debug-windows-x86_64\Nitrogen\Nitrogen.lib" "%ProjectPath%\backend\lib"
copy "%EnginePath%\vendor\GLFW\bin\Debug-windows-x86_64\GLFW\GLFW.lib" "%ProjectPath%\backend\lib"
copy "%EnginePath%\vendor\Glad\bin\Debug-windows-x86_64\Glad\Glad.lib" "%ProjectPath%\backend\lib"
copy "%EnginePath%\vendor\imgui\bin\Debug-windows-x86_64\ImGui\ImGui.lib" "%ProjectPath%\backend\lib"

:: Pause to display a message before closing
echo Project setup complete! Check the "premake5.lua" file in your project folder.
pause