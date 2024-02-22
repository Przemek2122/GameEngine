// See https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Renderer/Map/Map.h"

FMap::FMap(FMapAsset* InMapAsset)
	: MapAsset(InMapAsset)
	, bIsLoaded(false)
{
}

void FMap::Draw()
{
	if (bIsLoaded)
	{

	}
}

void FMap::Load()
{
	MapAsset->LoadMap();

	bIsLoaded = MapAsset->IsLoaded();
}

void FMap::ClearData()
{
	MapAsset->ClearMapData();

	bIsLoaded = true;
}

void FMap::Save()
{
	MapAsset->SaveMapData();
}
