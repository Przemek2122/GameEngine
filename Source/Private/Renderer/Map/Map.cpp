// See https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Renderer/Map/Map.h"

#include "Assets/Assets/TextureAsset.h"
#include "ECS/Entities/CameraManager.h"
#include "Misc/Math.h"
#include "Renderer/Map/MapManager.h"

FMap::FMap(FMapAsset* InMapAsset, FMapManager* InMapManager)
	: MapAsset(InMapAsset)
	, MapManager(InMapManager)
	, bIsActive(false)
	, Scale(0.f)
	, ScaleJump(0.f)
	, CameraManagerEntity(nullptr)
{
}

void FMap::Initialize()
{
	ReadAsset();

	FEntityManager* EntityManager = MapManager->GetOwnerWindow()->GetEntityManager();
	if (EntityManager != nullptr)
	{
		CameraManagerEntity = EntityManager->CreateEntity<ECameraManager>("CameraManager");
	}
	else
	{
		LOG_WARN("EntityManager is nullptr. CameraManager will not be created.");
	}
}

void FMap::DeInitialize()
{
	ClearData();

	FEntityManager* EntityManager = MapManager->GetOwnerWindow()->GetEntityManager();
	if (EntityManager != nullptr)
	{
		EntityManager->DestroyEntity(CameraManagerEntity);
	}
	else if (EntityManager == nullptr)
	{
		LOG_ERROR("EntityManager is nullptr. Memory leak!");
	}
}

int FMap::GetMapWidth() const
{
	return MapData.MapArray[0].Array.Size();
}

int FMap::GetMapHeight() const
{
	return MapData.MapArray.Size();
}

FVector2D<int> FMap::GetMapSizeInTiles() const
{
	return { GetMapWidth(), GetMapHeight() };
}

FVector2D<int> FMap::GetMapSizeInPixels() const
{
	return { GetMapWidth() * MapData.AssetsTileSize.X, GetMapHeight() * MapData.AssetsTileSize.Y };
}

void FMap::Draw()
{
	if (bIsActive)
	{
		const FVector2D<float> OwnerWindowSize = MapManager->GetOwnerWindow()->GetWindowSize();
		const FVector2D<float> MapLocationFloat = MapLocation;
		const FVector2D<float> MapAssetsTileSizeFloat = MapData.AssetsTileSize;

		// Minimal render tile offset - Everything before that vector will not be rendered
		FVector2D<int> MapLocationTileOffsetMin;
		MapLocationTileOffsetMin.X = FMath::FloorToInt(MapLocationFloat.X / MapAssetsTileSizeFloat.X);
		MapLocationTileOffsetMin.Y = FMath::FloorToInt(MapLocationFloat.Y / MapAssetsTileSizeFloat.Y);

		MapLocationTileOffsetMin.X = FMath::Max(MapLocationTileOffsetMin.X, 0);
		MapLocationTileOffsetMin.Y = FMath::Max(MapLocationTileOffsetMin.Y, 0);

		// Maximal render tile offset - Everything after that vector will not be rendered
		FVector2D<int> MapLocationTileOffsetMax = MapLocationTileOffsetMin;
		MapLocationTileOffsetMax.X += FMath::CeilToInt(OwnerWindowSize.X / MapAssetsTileSizeFloat.X);
		MapLocationTileOffsetMax.Y += FMath::CeilToInt(OwnerWindowSize.Y / MapAssetsTileSizeFloat.Y);

		SDL_Renderer* WindowRenderer = MapManager->GetOwnerWindow()->GetRenderer()->GetSDLRenderer();

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

					Destination.x = MapLocation.X + HorizontalIndex * MapData.AssetsTileSize.X;
					Destination.y = MapLocation.Y + VerticalIndex * MapData.AssetsTileSize.Y;

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
	MapData.Clear();

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

void FMap:: AddMapLocation(const FVector2D<int>& LocationChange)
{
	MapLocation += LocationChange;

	const FVector2D<int> MapSize = GetMapSizeInPixels();
	const FVector2D<int> WindowSize = MapManager->GetOwnerWindow()->GetWindowSize();
	const FVector2D<int> HalfWindowSize = WindowSize / 2;

	// Width right limit
	if (MapLocation.X > HalfWindowSize.X)
	{
		MapLocation.X = HalfWindowSize.X;
	}
	// Width left limit
	else if (MapLocation.X < -MapSize.X + HalfWindowSize.X)
	{
		MapLocation.X = -MapSize.X + HalfWindowSize.X;
	}

	// Height down limit
	if (MapLocation.Y > HalfWindowSize.Y)
	{
		MapLocation.Y = HalfWindowSize.Y;
	}
	// Height up limit
	else if (MapLocation.Y < -MapSize.Y + HalfWindowSize.Y)
	{
		MapLocation.Y = -MapSize.Y + HalfWindowSize.Y;
	}
}

FVector2D<int> FMap::GetMapLocation() const
{
	return MapLocation;
}
