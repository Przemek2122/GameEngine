// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

class FFilesystem
{
public:
	static bool CreateFolder(const std::string& Path);
	static bool DeleteFolder(const std::string& Path, const bool bRecursive = false);
	static bool FileExists(const std::string& InPath);

	
	/** @returns slash for current filesystem */
	static char* GetPlatformSlash();

	/** @returns assets directory name */
	static char* GetAssetDirName();
	
};
