// See https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Assets/Assets/MapAsset.h"
#include "Renderer/Map/Map.h"
#include "Renderer/Map/Mapmanager.h"

FMapManager::FMapManager(FWindow* InWindow)
	: CurrentMap(nullptr)
	, Window(InWindow)
{
}

FMapManager::~FMapManager()
{
	if (CurrentMap != nullptr)
	{
		delete CurrentMap;
	}
}

void FMapManager::DrawMap()
{
	if (CurrentMap != nullptr)
	{
		CurrentMap->Draw();
	}
}

FMapAsset* FMapManager::LoadMap(const std::string& Name)
{
	const FAssetsManager* AssetsManager = GEngine->GetAssetsManager();
	if (AssetsManager != nullptr)
	{
		FMapAsset* MapAsset = AssetsManager->GetAsset<FMapAsset>(Name);
		if (MapAsset != nullptr)
		{
			if (!MapAsset->IsLoaded())
			{
				MapAsset->SetMapManager(this);

				MapAsset->LoadMap();
			}

			return MapAsset;
		}
		else
		{
			LOG_ERROR("Map not found: " + Name);
		}
	}

	return nullptr;
}

void FMapManager::UnLoadMap(const std::string& Name)
{
	if (!Name.empty())
	{
		FMapAsset* MapAsset = GetMapByName(Name);
		if (MapAsset != nullptr)
		{
			UnLoadMap(MapAsset);
		}
		else
		{
			LOG_ERROR("Map not found: " + Name);
		}
	}
	else
	{
		LOG_ERROR("Map name is empty.");
	}
}

void FMapManager::UnLoadMap(FMapAsset* MapAsset)
{
	if (MapAsset != nullptr && MapAsset->IsLoaded())
	{
		if (IsMapAssetCurrentlyUsed(MapAsset))
		{
			LOG_ERROR("Tried to unload current map. This is not allowed. Use DeactivateCurrentMap first instead.");
		}
		else
		{
			MapAsset->ClearMapData();
		}
	}
}

void FMapManager::UnloadAllMaps()
{
	for (FMapAsset* MapAsset : MapAssets)
	{
		UnLoadMap(MapAsset);
	}
}

FMapAsset* FMapManager::GetMapByName(const std::string& Name)
{
	const FAssetsManager* AssetsManager = GEngine->GetAssetsManager();
	if (AssetsManager != nullptr)
	{
		FMapAsset* MapAsset = AssetsManager->GetAsset<FMapAsset>(Name);
		if (MapAsset != nullptr)
		{
			if (MapAsset->IsLoaded())
			{
				return MapAsset;
			}
			else
			{
				LOG_WARN("Map is not loaded. Load it first.");
			}
		}
	}

	return nullptr;
}

void FMapManager::SetActiveMap(FMapAsset* MapAsset)
{
	if (MapAsset != nullptr)
	{
		if (MapAsset->IsLoaded())
		{
			if (CurrentMap != nullptr)
			{
				DeactivateCurrentMap();
			}

			CurrentMap = new FMap(MapAsset, this);
			CurrentMap->Initialize();
		}
		else
		{
			LOG_ERROR("Map is not loaded. Load it first.");
		}
	}
	else
	{
		LOG_ERROR("Map is nullptr.");
	}
}

void FMapManager::DeactivateCurrentMap()
{
	if (CurrentMap != nullptr)
	{
		CurrentMap->DeInitialize();

		delete CurrentMap;

		CurrentMap = nullptr;
	}
}

void FMapManager::CacheAvailableMaps()
{
	FAssetsManager* AssetsManager = GEngine->GetAssetsManager();
	if (AssetsManager != nullptr)
	{
		AvailableMaps.Clear();

		CArray<std::string> DirectoriesFound = AssetsManager->GetFilesFromDirectory(AssetsManager->GetMapsPathRelative());

		const char Slash = AssetsManager->GetPlatformSlash();

		const std::string PathPrefix = AssetsManager->GetMapsPathRelative() + Slash;

		for (std::string& Directory : DirectoriesFound)
		{
			std::string Path = PathPrefix + Directory;

			AssetsManager->AddAsset<FMapAsset>(Directory, Path);

			AvailableMaps.Push(Directory);
		}
	}
}

CArray<std::string> FMapManager::GetAvailableMaps() const
{
#if _DEBUG
	if (AvailableMaps.IsEmpty())
	{
		// Maps are empty,
		// either you forgot to call FMapManager::CacheAvailableMaps
		// or
		// maps are really empty
		ENSURE_VALID(false);
	}
#endif

	return AvailableMaps;
}

bool FMapManager::IsMapAssetCurrentlyUsed(const FMapAsset* MapAsset)
{
	return (CurrentMap != nullptr && CurrentMap->GetMapAsset() == MapAsset);
}
