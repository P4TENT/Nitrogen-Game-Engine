@echo off 
 
:: Get The Paths 
cd "../.." 	
set "ProjectPath=%cd%" 	
cd "../../Nitrogen" 
set "EnginePath=%cd%" 
 
:: Get Project Name 
for %%F in ("%ProjectPath%") do set "ProjectName=%%~nF" 
 
:: Copy the src folder for dependencies 
mkdir "%ProjectPath%\bin\Debug-windows-x86_64\%ProjectName%\src\assets" 
xcopy "%ProjectPath%\%ProjectName%\src\assets" "%ProjectPath%\bin\Debug-windows-x86_64\%ProjectName%\src\assets" /E /I /Y 
 
:: Run the Application 
cd "%ProjectPath%\bin\Debug-windows-x86_64\%ProjectName%" 
call "%ProjectName%.exe" 
