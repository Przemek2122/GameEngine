echo on

REM SAMPLE - In post build:
REM call $(GameEngineDir)\Scripts\BuildActions\PostBuild\CopyDLLs.bat $(GameEngineDir)\Libs\$(Platform)\$(Configuration)\ $(SolutionDir)$(Platform)\$(Configuration)\

set LibsSourcePath=%1
set LibsTargetPath=%2

xcopy %LibsSourcePath%*.dll %LibsTargetPath% /S /Y
