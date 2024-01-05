// See https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Assets/Assets/MapAsset.h"
#include "Renderer/Map/Mapmanager.h"

FMapManager::FMapManager()
{
}

FMapManager::~FMapManager()
{
}

void FMapManager::LoadMap(const std::string& Name)
{
	FAssetsManager* AssetsManager = Engine->GetAssetsManager();
	if (AssetsManager != nullptr)
	{
		FMapAsset* Asset = AssetsManager->GetAsset<FMapAsset>(Name);
		if (Asset != nullptr)
		{
			Asset->LoadMap();
		}
		else
		{
			// Missing asset
			ENSURE_VALID(false);
		}
	}
}

void FMapManager::UnLoadMap(const std::string& Name)
{
}

void FMapManager::CacheAvailableMaps()
{
	FAssetsManager* AssetsManager = Engine->GetAssetsManager();
	if (AssetsManager != nullptr)
	{
		CArray<std::string> DirectoriesFound = AssetsManager->GetFilesFromDirectory(AssetsManager->GetMapsPathRelative());

		const char* Slash = AssetsManager->GetPlatformSlash();

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
