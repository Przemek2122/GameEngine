REM Go to main directory
cd ..
cd ..

echo "Clear old includes..."

REM Remove old directories
DEL /S /F /Q Source\ThirdParty\SDL3
DEL /S /F /Q Source\ThirdParty\libuv

echo "Create copy of includes..."

REM Make copy of new ones
XCOPY /Y /E /V ThirdParty\SDL\include\SDL3\* Source\ThirdParty\SDL3\*
XCOPY /Y /E /V ThirdParty\SDL_mixer\include\SDL3_mixer\* Source\ThirdParty\SDL3\*
XCOPY /Y /E /V ThirdParty\SDL_ttf\include\SDL3_ttf\* Source\ThirdParty\SDL3\*
XCOPY /Y /E /V ThirdParty\SDL_image\include\SDL3_image\* Source\ThirdParty\SDL3\*

XCOPY /Y /E /V ThirdParty\libuv\include\* Source\ThirdParty\libuv\*

echo "Coping includes finished."
