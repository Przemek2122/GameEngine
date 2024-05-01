// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "Assets/Assets/IniAsset.h"

#include "Assets/Parser.h"

FIniAsset::FIniAsset(const std::string& InAssetName, const std::string& InAssetPath)
	: FAssetBase(InAssetName, InAssetPath)
{
}

FIniAsset::~FIniAsset()
{
}

EAssetType FIniAsset::GetAssetType() const
{
	return EAssetType::AT_INI;
}

std::string FIniAsset::GetAbsolutePath() const
{
	return GEngine->GetAssetsManager()->ConvertRelativeToFullPath(AssetPath);
}

bool FIniAsset::DoesFileExist() const
{
	std::string AbsolutePath = GetAbsolutePath();

	return FFileSystem::File::Exists(AbsolutePath);
}

void FIniAsset::Load(FParser* IniParser)
{
	if (IniParser != nullptr && DoesFileExist())
	{
		std::string AbsolutePath = GetAbsolutePath();

		FDelegateSafe<void, const std::string&> FileReaderDelegate;
		FileReaderDelegate.BindLambda([&](const std::string& Line)
		{
			CArray<FParserLine> ParserLines = IniParser->ParseStringIntoLines(Line);

			Lines += ParserLines;
		});

		FFileSystem::File::GetFileContentLineByLine(FileReaderDelegate, AbsolutePath);
	}
}

void FIniAsset::Save(FParser* IniParser)
{
	if (IniParser != nullptr)
	{
		
	}
}

void FIniAsset::UnLoad()
{
}
