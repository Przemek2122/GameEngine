REM Go to main directory
cd ..
cd ..

echo "Creating copy of libraries..."

set Configuration=Debug
set Platform=x64

set TargetLocation=Libs

REM Copy libs

REM SDL_Image
XCOPY /Y /E /V /-I ThirdParty\SDL_image\VisualC\%Platform%\%Configuration%\*.dll %TargetLocation%\%Platform%\%Configuration%\*.dll
XCOPY /Y /E /V /-I ThirdParty\SDL_image\VisualC\%Platform%\%Configuration%\*.lib %TargetLocation%\%Platform%\%Configuration%\*.lib
XCOPY /Y /E /V /-I ThirdParty\SDL_image\VisualC\%Platform%\%Configuration%\*.pdb %TargetLocation%\%Platform%\%Configuration%\*.pdb

REM SDL_Mixer
XCOPY /Y /E /V /-I ThirdParty\SDL_mixer\VisualC\%Platform%\%Configuration%\*.dll %TargetLocation%\%Platform%\%Configuration%\*.dll
XCOPY /Y /E /V /-I ThirdParty\SDL_mixer\VisualC\%Platform%\%Configuration%\*.lib %TargetLocation%\%Platform%\%Configuration%\*.lib
XCOPY /Y /E /V /-I ThirdParty\SDL_mixer\VisualC\%Platform%\%Configuration%\*.pdb %TargetLocation%\%Platform%\%Configuration%\*.pdb

REM SDL_ttf
XCOPY /Y /E /V /-I ThirdParty\SDL_ttf\VisualC\%Platform%\%Configuration%\*.dll %TargetLocation%\%Platform%\%Configuration%\*.dll
XCOPY /Y /E /V /-I ThirdParty\SDL_ttf\VisualC\%Platform%\%Configuration%\*.lib %TargetLocation%\%Platform%\%Configuration%\*.lib
XCOPY /Y /E /V /-I ThirdParty\SDL_ttf\VisualC\%Platform%\%Configuration%\*.pdb %TargetLocation%\%Platform%\%Configuration%\*.pdb

REM SDL
XCOPY /Y /E /V /-I ThirdParty\SDL\VisualC\%Platform%\%Configuration%\SDL3.dll %TargetLocation%\%Platform%\%Configuration%\SDL3.dll
XCOPY /Y /E /V /-I ThirdParty\SDL\VisualC\%Platform%\%Configuration%\SDL3.lib %TargetLocation%\%Platform%\%Configuration%\SDL3.lib
XCOPY /Y /E /V /-I ThirdParty\SDL\VisualC\%Platform%\%Configuration%\SDL3.pdb %TargetLocation%\%Platform%\%Configuration%\SDL3.pdb

echo "Copy of libraries finishd."

PAUSE