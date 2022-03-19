echo on

REM SAMPLE - In post build:
REM call $(GameEngineDir)\Script\BuildActions\PostBuild\CopyDLLs.bat $(GameEngineDir)\Libs\ $(SolutionDir)$(Platform)\$(Configuration)\ x86

xcopy %1SDL\%3\*.dll %2 /S /Y
xcopy %1SDL_Image\%3\*.dll %2 /S /Y
xcopy %1SDL_Mixer\%3\*.dll %2 /S /Y
xcopy %1SDL_TTF\%3\*.dll %2 /S /Y

