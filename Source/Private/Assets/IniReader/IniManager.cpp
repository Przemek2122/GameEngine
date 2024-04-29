#include "CoreEngine.h"
#include "Assets/IniReader/IniManager.h"

#include "Assets/Parser.h"
#include "Assets/IniReader/IniObject.h"

FIniManager::FIniManager(FAssetsManager* InAssetsManager)
	: InSeparatorCharArray({ '\n' })
	, InCommentCharArray({ ';', '#' })
	, InIgnoredCharArray({ ' ', '	' })
	, AssetsManager(InAssetsManager)
{
	IniParser = std::make_shared<FParser>(InSeparatorCharArray, InCommentCharArray, InIgnoredCharArray);
}

std::shared_ptr<FIniObject> FIniManager::GetIniObject(const std::string& IniName)
{
	std::shared_ptr<FIniObject> IniObject;

	if (IniNameToObjectMap.ContainsKey(IniName))
	{
		IniObject = IniNameToObjectMap.FindValueByKey(IniName);
	}
	else
	{
		IniObject = CreateIniObject(IniName);
	}

	return IniObject;
}

FParser* FIniManager::GetIniParser() const
{
	return IniParser.get();
}

FAssetsManager* FIniManager::GetAssetsManager() const
{
	return AssetsManager;
}

std::shared_ptr<FIniObject> FIniManager::CreateIniObject(const std::string& IniName)
{
	std::string IniFullPath = ConvertIniNameToRelativeFullPath(IniName);

	std::shared_ptr<FIniObject> SharedPtr = std::make_shared<FIniObject>(this, IniFullPath, IniName);

	SharedPtr->Initialize();

	IniNameToObjectMap.Emplace(IniName, SharedPtr);

	return SharedPtr;
}

std::string FIniManager::ConvertIniNameToRelativeFullPath(const std::string& IniName) const
{
	std::string FullPath;

	FullPath += AssetsManager->GetConfigPathRelative();
	FullPath += IniName;

	return FullPath;
}
