cd ..
cd ..

SET CONFIGURATION="Debug"

SET ThirdParty_PATH=%cd%\ThirdParty
SET PROJECT_SDL_PATH="%ThirdParty_PATH%\SDL\VisualC\SDL.sln"
SET PROJECT_SDL_IMAGE_PATH="%ThirdParty_PATH%\SDL_image\VisualC\SDL_image.sln"
SET PROJECT_SDL_Mixer_PATH="%ThirdParty_PATH%\SDL_mixer\VisualC\SDL_mixer.sln"
SET PROJECT_SDL_TTF_PATH="%ThirdParty_PATH%\SDL_ttf\VisualC\SDL_ttf.sln"

REM devenv is located in 'C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE'
REM In case it's missing add it to your env variables
REM Optional Debug|Win32
devenv %PROJECT_SDL_PATH% /Build %CONFIGURATION%
devenv %PROJECT_SDL_IMAGE_PATH% /Build %CONFIGURATION%
devenv %PROJECT_SDL_Mixer_PATH% /Build %CONFIGURATION%
devenv %PROJECT_SDL_TTF_PATH% /Build %CONFIGURATION%

REM Build libuv using cmake
cd ThirdParty\libuv

mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64

REM go back to main dir (GameEngine\)
cd ..
cd ..

REM Build libuv using visual 
devenv %ThirdParty_PATH%/libuv/build/libuv.sln /Build %CONFIGURATION%

PAUSE