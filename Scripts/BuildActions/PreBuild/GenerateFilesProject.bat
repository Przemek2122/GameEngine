echo on

REM SAMPLE - In pre build:
REM call $(GameEngineDir)\BuildActions\PreBuild\GenerateFilesProject.bat $(SolutionDir) 

call "..\..\SubPrograms\GenerateFiles\Release\GenerateFiles.exe" %1 %2
