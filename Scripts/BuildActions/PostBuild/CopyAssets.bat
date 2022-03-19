echo on

REM SAMPLE - In post build:
REM call $(GameEngineDir)\Script\BuildActions\PostBuild\CopyAssets.bat $(GameEngineDir)\Assets\ $(SolutionDir)$(Platform)\$(Configuration)\ x86

xcopy %1\* %2\Assets\ /S /Y

