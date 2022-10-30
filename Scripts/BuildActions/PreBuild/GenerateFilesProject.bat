echo on

REM SAMPLE - In pre build:
REM call $(GameEngineDir)\BuildActions\Scripts\PreBuild\GenerateFilesProject.bat $(SolutionDir) 

REM 
REM call "%~dp0..\..\..\SubPrograms\GenerateFiles\Release\GenerateFiles.exe" %1 %2
call D:\Repos\GameEngine\SubPrograms\GenerateFiles.exe %1 %2
