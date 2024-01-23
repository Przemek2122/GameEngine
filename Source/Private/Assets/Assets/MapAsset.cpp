// Created by Przemys³aw Wiewióra 2023

#include "CoreEngine.h"
#include "Assets/Assets/MapAsset.h"
#include "Assets/Assets/TextureAsset.h"
#include "Assets/Parser.h"
#include "Renderer/Map/MapManager.h"

FMapAsset::FMapAsset(const std::string& InAssetName, const std::string& InAssetPath)
	: FAssetBase(InAssetName, InAssetPath)
	, bIsLoaded(false)
	, AssetsTileSize(32, 32)
	, MapManager(nullptr)
{
}

FMapAsset::~FMapAsset()
{
	UnLoadMap();
}

void FMapAsset::SetMapManager(FMapManager* InMapManager)
{
	MapManager = InMapManager;
}

void FMapAsset::LoadMap()
{
	if (FFilesystem::DirectoryExists(AssetPath))
	{
		const std::string SharedBeginning = AssetPath + GEngine->GetAssetsManager()->GetPlatformSlash();
		const std::string SharedBeginningFiles = SharedBeginning + AssetName;

		MapNameFilePath = SharedBeginningFiles + '.' + FMapFilesExtensions::PrimaryMapFileExtension;
		MapDataFilePath = SharedBeginningFiles + '.' + FMapFilesExtensions::MapDataFileExtension;

		for (const std::string& AssetDirectoryName : FMapFilesExtensions::AssetDirectoryNames)
		{
			const std::string Path = SharedBeginning + AssetDirectoryName;

			if (FFilesystem::DirectoryExists(Path))
			{
				MapAssetsDirPath = Path;

				break;
			}
		}

		// Ensure all required files exists
		if (	FFilesystem::FileExists(MapNameFilePath) 
			&&	FFilesystem::FileExists(MapDataFilePath) 
			&&	FFilesystem::DirectoryExists(MapAssetsDirPath))
		{
			LOG_INFO("Loading map: " << AssetName);

			CArray<std::string> MapAssetFiles = FFilesystem::GetFilesFromDirectory(MapAssetsDirPath);

			FParser Parser({ ',' });

			FAssetsManager* AssetsManager = GEngine->GetAssetsManager();

			SDL_Renderer* WindowRenderer = MapManager->GetWindow()->GetRenderer()->GetSDLRenderer();

			// Map assets
			std::ifstream MapDataFilePathStream(MapDataFilePath);
			for (std::string Line; getline(MapDataFilePathStream, Line); )
			{
				CArray<std::string> StringArray = Parser.ParseLineIntoStrings(Line);
				if (StringArray.Size() == 3)
				{
					FMapSubAssetSettings MapSubAssetSettings;
					MapSubAssetSettings.AssetIndex = atoi(StringArray[0].c_str());
					MapSubAssetSettings.Collision = atoi(StringArray[1].c_str());

					std::string SubAsset = StringArray[2];

					std::string SubAssetName = AssetName + SubAsset;

					char* Slash = AssetsManager->GetPlatformSlash();
					std::string SubAssetAbsolutePath = MapAssetsDirPath + Slash + SubAsset;

					std::shared_ptr<FTextureAsset> Asset = AssetsManager->CreateAssetFromAbsolutePath<FTextureAsset>(SubAssetName, SubAssetAbsolutePath);
					Asset->PrepareTexture(WindowRenderer);

					MapSubAssetSettings.TextureAssetPtr = Asset;

					MapSubAssetSettingsArray.Push(MapSubAssetSettings);
				}
			}
			MapDataFilePathStream.close();

			const int MaxAssetIndex = MapSubAssetSettingsArray.Size();

			// Map, where should be which tile
			std::ifstream MapNameFilePathStream(MapNameFilePath);
			for (std::string Line; getline(MapNameFilePathStream, Line); )
			{
				CArray<std::string> ParsedArray = Parser.ParseLineIntoStrings(Line);

				FMapRow MapRow;

				for (std::string& Element : ParsedArray)
				{
					// @TODO Could switch to strtol to make sure conversion does not fail
					const int Index = atoi(Element.c_str());

					if (Index >= MaxAssetIndex)
					{
						LOG_ERROR("Found invalid index: '" << Index << "' Plase make sure asset for that index exists.");

						MapRow.Array.Push(INDEX_INCORRECT);
					}
					else
					{
						MapRow.Array.Push(Index);
					}
				}

				MapArray.Push(MapRow);
			}
			MapNameFilePathStream.close();

			bIsLoaded = true;

			LOG_INFO("Map assets: " << MapSubAssetSettingsArray.Size() << " loaded, map name: " << AssetName);
		}
		else
		{
			LOG_ERROR("Missing map files for: " << AssetName);
		}
	}
	else
	{
		LOG_ERROR("Missing directory for map.");
	}
}

void FMapAsset::UnLoadMap()
{
	MapNameFilePath.clear();
	MapDataFilePath.clear();
	MapAssetsDirPath.clear();
	MapLines.Clear();
	MapSubAssetSettingsArray.Clear();

	bIsLoaded = false;
}

bool FMapAsset::IsLoaded() const
{
	return bIsLoaded;
}

void FMapAsset::Draw()
{
	if (bIsLoaded)
	{
		SDL_Renderer* WindowRenderer = MapManager->GetWindow()->GetRenderer()->GetSDLRenderer();

		SDL_Rect Source, Destination;
		Source.x = 0;
		Source.y = 0;
		Source.h = AssetsTileSize.Y;
		Source.w = AssetsTileSize.X;
		Destination.h = AssetsTileSize.Y;
		Destination.w = AssetsTileSize.X;

		const int VerticalSize = MapArray.Size();

		for (int VerticalIndex = 0; VerticalIndex < VerticalSize; VerticalIndex++)
		{
			const FMapRow& MapRow = MapArray[VerticalIndex];

			const int HorizontalSize = MapRow.Array.Size();

			for (int HorizontalIndex = 0; HorizontalIndex < HorizontalSize; HorizontalIndex++)
			{
				const int AssetIndex = MapRow.Array[HorizontalIndex];
				if (AssetIndex >= 0)
				{
					const FMapSubAssetSettings CurrentAssetSettings = MapSubAssetSettingsArray[AssetIndex];

					Destination.x = HorizontalIndex * AssetsTileSize.X;
					Destination.y = VerticalIndex * AssetsTileSize.Y;

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
