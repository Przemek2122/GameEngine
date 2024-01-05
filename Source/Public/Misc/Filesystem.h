// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

class FFilesystem
{
public:
	static bool CreateFolder(const std::string& Path);
	static bool DeleteFolder(const std::string& Path, const bool bRecursive = false);
	static bool FileExists(const std::string& InPath);
	static bool DirectoryExists(const std::string& InPath);

	/** @returns files from given directory, optionally recursive */
	static CArray<std::string> GetFilesFromDirectory(const std::string& Path, const bool bRecursive = false);

	/** @returns directory names from given location */
	static CArray<std::string> GetDirectories(const std::string& Path, const bool bCovertToJustFolders = false);
	
	/** @returns slash for current filesystem */
	static char* GetPlatformSlash();

private:
	static void GetFilesFromDirectoryRecursive(CArray<std::string>& Container, const std::filesystem::directory_entry& Entry, const bool bRecursive);

};
