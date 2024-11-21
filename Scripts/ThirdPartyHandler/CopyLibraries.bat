REM Go to main directory
cd ..
cd ..

echo "Creating copy of libraries..."

set Configuration="Debug"

REM Copy libs
REM SDL
XCOPY /Y /E /V /-I ThirdParty\SDL\VisualC\x64\Debug\SDL3.dll Libs\SDL\x64\Debug\SDL.dll
XCOPY /Y /E /V /-I ThirdParty\SDL\VisualC\x64\Debug\SDL3.lib Libs\SDL\x64\Debug\SDL.lib
XCOPY /Y /E /V /-I ThirdParty\SDL\VisualC\x64\Debug\SDL3.pdb Libs\SDL\x64\Debug\SDL.pdb

REM SDL_Image


REM SDL_ttf


REM SDL_Mixer

echo "Copy of libraries finishd."