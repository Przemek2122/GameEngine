// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Misc/Filesystem.h"

namespace fs = std::filesystem;

static char* AssetsDir = TEXT("Assets");
static char* PlatformSlash = TEXT("\\");

bool FFilesystem::CreateFolder(const std::string& Path)
{
    return fs::create_directory(Path);
}

bool FFilesystem::DeleteFolder(const std::string& Path, const bool bRecursive)
{
    if (bRecursive)
    {
        return fs::remove_all(Path);
    }
    else
    {
        return fs::remove(Path) != false;
    }
}

bool FFilesystem::FileExists(const std::string& InPath)
{
	std::ifstream FileCheck(InPath.c_str());
    return FileCheck.good();
}

char* FFilesystem::GetPlatformSlash()
{
	return PlatformSlash;
}

char* FFilesystem::GetAssetDirName()
{
	return AssetsDir;
}
