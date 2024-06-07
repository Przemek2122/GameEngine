# GameEngine

Game engine for 2D rendering using SDL.
It's made as library so you can include it anywhere.
Currrently it's windows only but it's based on cross-platform SDL2

Visual studio 2022 / C++17

Easiest way to create new project based on this engine:
Use template:	https://github.com/Przemek2122/GameEngineSampleProject

Documentation (In progress):
https://drive.google.com/drive/folders/1MfwG8kNNMIjEoOrjeFlehiW3WVINps8b?usp=drive_link

If GameEngine project fails to load Click it in solution and change it's project file in right bottom of properties. Than reload.
1.	Inside project you could change path to engine 
	https://docs.microsoft.com/en-us/cpp/build/create-reusable-property-configurations?view=msvc-160#to-create-a-property-sheet
	On the menu bar, choose View > Property Manager or View > Other Windows > Property Manager. The Property Manager opens.

2.	You can also edit directly GameEngine.props (Located BOTH in project directory and engine this is TODO subject):
	GameEngineDir = '../GameEngine'

# Currently supported futures
 - Entity with components	- https://github.com/Przemek2122/GameEngine/tree/main/Source/Public/Core/ECS
 - 'Widgets' for UI			- https://github.com/Przemek2122/GameEngine/tree/main/Source/Public/Renderer/Widgets
 - Simple map with editor	- https://github.com/Przemek2122/GameEngine/tree/main/Source/Public/Renderer/Map
 - Ini files				- https://github.com/Przemek2122/GameEngine/blob/main/Assets/Config/EngineInput.ini

