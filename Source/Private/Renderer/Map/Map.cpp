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
	, CameraManagerEntity(nullptr)
	, MapLocationChangeDelegate()
	, bIsActive(false)
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
		const FVector2D<float> MapLocationFloat = MapRenderOffset;
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

					Destination.x = MapRenderOffset.X + HorizontalIndex * MapData.AssetsTileSize.X;
					Destination.y = MapRenderOffset.Y + VerticalIndex * MapData.AssetsTileSize.Y;

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

bool FMap::IsInBounds(const FVector2D<int>& Location) const
{
	const FVector2D<int> LocationMinusOffset = Location - MapRenderOffset;
	const FVector2D<int> MapSize = GetMapSizeInPixels();

	return (	(LocationMinusOffset.X >= 0 && LocationMinusOffset.X < MapSize.X)	&& 
				(LocationMinusOffset.Y >= 0 && LocationMinusOffset.Y < MapSize.Y)	);
}

void FMap::AddMapRenderOffset(const FVector2D<int>& LocationChange)
{
	MapRenderOffset += LocationChange;

	const FVector2D<int> MapSize = GetMapSizeInPixels();
	const FVector2D<int> WindowSize = MapManager->GetOwnerWindow()->GetWindowSize();
	const FVector2D<int> HalfWindowSize = WindowSize / 2;

	// Width right limit
	if (MapRenderOffset.X > HalfWindowSize.X)
	{
		MapRenderOffset.X = HalfWindowSize.X;
	}
	// Width left limit
	else if (MapRenderOffset.X < -MapSize.X + HalfWindowSize.X)
	{
		MapRenderOffset.X = -MapSize.X + HalfWindowSize.X;
	}

	// Height down limit
	if (MapRenderOffset.Y > HalfWindowSize.Y)
	{
		MapRenderOffset.Y = HalfWindowSize.Y;
	}
	// Height up limit
	else if (MapRenderOffset.Y < -MapSize.Y + HalfWindowSize.Y)
	{
		MapRenderOffset.Y = -MapSize.Y + HalfWindowSize.Y;
	}

	// Trigger delegate for changed location
	MapLocationChangeDelegate.Execute(MapRenderOffset);
}

FVector2D<int> FMap::GetMapRenderOffset() const
{
	return MapRenderOffset;
}

FDelegate<void, FVector2D<int>>& FMap::GetMapLocationChangeDelegate()
{
	return MapLocationChangeDelegate;
}

void FMap::ChangeTileAtLocation(const FVector2D<int>& Location, const int MapAssetIndexToSet)
{
	const bool bDoesAssetIndexExists = MapData.MapSubAssetSettingsArray.IsValidIndex(MapAssetIndexToSet);

	if (bDoesAssetIndexExists)
	{
		const FVector2D<int> AbsoluteLocation = Location - MapRenderOffset;

		FVector2D<int> TileLocation;
		TileLocation.X = FMath::CeilToInt(static_cast<float>(AbsoluteLocation.X) / static_cast<float>(MapData.AssetsTileSize.X)) - 1;
		TileLocation.Y = FMath::CeilToInt(static_cast<float>(AbsoluteLocation.Y) / static_cast<float>(MapData.AssetsTileSize.Y)) - 1;

		if (MapData.MapArray.IsValidIndex(TileLocation.Y))
		{
			FMapRow& MapRow = MapData.MapArray[TileLocation.Y];

			if (MapRow.Array.IsValidIndex(TileLocation.X))
			{
				MapRow.Array[TileLocation.X] = MapAssetIndexToSet;
			}
		}
	}
	else
	{
		LOG_WARN("Location is out of bounds.");
	}
}
