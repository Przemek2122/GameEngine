# GameEngine

Game engine for 2D rendering using SDL.
It's made as library so you can include it anywhere.

Currently moving existing code.

Visual studio 2019 / C++17

Easiest way to create new project based on this engine:
Copy https://github.com/Przemek2122/SimpleShooterGame

If GameEngine project fails to load Click it in solution and change it's project file in right bottom of properties. Than reload.

Inside project you could change path to engine 
https://docs.microsoft.com/en-us/cpp/build/create-reusable-property-configurations?view=msvc-160#to-create-a-property-sheet
On the menu bar, choose View > Property Manager or View > Other Windows > Property Manager. The Property Manager opens.

Setting Macro (You can also edit directly GameEngine.props):
GameEngineDir = '../GameEngine'
