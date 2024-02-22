// See https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Renderer/Map/Map.h"

#include "Assets/Assets/TextureAsset.h"
#include "Renderer/Map/MapManager.h"

FMap::FMap(FMapAsset* InMapAsset, FMapManager* InMapManager)
	: MapAsset(InMapAsset)
	, MapManager(InMapManager)
	, bIsActive(false)
{
}

void FMap::Initialize()
{
	ReadAsset();
}

void FMap::Draw()
{
	if (bIsActive)
	{
		SDL_Renderer* WindowRenderer = MapManager->GetWindow()->GetRenderer()->GetSDLRenderer();

		SDL_Rect Source, Destination;
		Source.x = 0;
		Source.y = 0;
		Source.h = MapData.AssetsTileSize.Y;
		Source.w = MapData.AssetsTileSize.X;
		Destination.h = MapData.AssetsTileSize.Y;
		Destination.w = MapData.AssetsTileSize.X;

		const int VerticalSize = MapData.MapArray.Size();

		for (int VerticalIndex = 0; VerticalIndex < VerticalSize; VerticalIndex++)
		{
			const FMapRow& MapRow = MapData.MapArray[VerticalIndex];

			const int HorizontalSize = MapRow.Array.Size();

			for (int HorizontalIndex = 0; HorizontalIndex < HorizontalSize; HorizontalIndex++)
			{
				const int AssetIndex = MapRow.Array[HorizontalIndex];
				if (AssetIndex >= 0)
				{
					const FMapSubAssetSettings CurrentAssetSettings = MapData.MapSubAssetSettingsArray[AssetIndex];

					Destination.x = HorizontalIndex * MapData.AssetsTileSize.X;
					Destination.y = VerticalIndex * MapData.AssetsTileSize.Y;

					CurrentAssetSettings.TextureAssetPtr->GetTexture()->Draw(WindowRenderer, Source, Destination);
				}
				else
				{
					// Do sth when index is not found

					// @TODO ...
				}
			}
		}
	}
}

void FMap::Load()
{
	MapAsset->LoadMap();

	bIsActive = MapAsset->IsLoaded();
}

void FMap::ClearData()
{
	MapAsset->ClearMapData();

	bIsActive = true;
}

void FMap::Save()
{
	MapAsset->SaveMapData();
}

void FMap::ReadAsset()
{
	if (MapAsset->IsMapDataValid())
	{
		MapData = MapAsset->GetMapData();

		bIsActive = true;
	}
}

void FMap::WriteAsset()
{
	MapAsset->WriteMapData(MapData);
}
