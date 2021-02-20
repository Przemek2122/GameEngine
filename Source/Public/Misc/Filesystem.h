// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

class FFilesystem
{
public:
	static bool CreateDirrectory(const std::string Path);

	static bool DeleteDirrectory(const std::string Path, const bool bRecursive = false);

	static bool FileExists(const std::string& InPath);

	/** @returns slash for current filesystem */
	static char* GetPlatformSlash();
	
};
