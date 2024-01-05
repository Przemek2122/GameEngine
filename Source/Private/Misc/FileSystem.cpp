// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Misc/Filesystem.h"

namespace fs = std::filesystem;

static char* PlatformSlash = TEXT_CHAR("\\");

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

bool FFilesystem::DirectoryExists(const std::string& InPath)
{
    return (std::filesystem::is_directory(InPath));
}

CArray<std::string> FFilesystem::GetFilesFromDirectory(const std::string& Path, const bool bRecursive)
{
    CArray<std::string> Files;

    for (const std::filesystem::directory_entry& Entry : fs::directory_iterator(Path))
    {
        GetFilesFromDirectoryRecursive(Files, Entry, bRecursive);
    }

    return Files;
}

CArray<std::string> FFilesystem::GetDirectories(const std::string& Path, const bool bCovertToJustFolders)
{
    CArray<std::string> Directories;

    for (const std::filesystem::directory_entry& Entry : fs::directory_iterator(Path))
    {
	    if (Entry.is_directory())
	    {
            auto PathEntry = Entry.path();

            if (bCovertToJustFolders)
            {
	            if (PathEntry.has_filename())
	            {
                    PathEntry = PathEntry.filename();
	            }
            }

            Directories.Push(PathEntry.string());
	    }
    }

    return Directories;
}

char* FFilesystem::GetPlatformSlash()
{
	return PlatformSlash;
}

void FFilesystem::GetFilesFromDirectoryRecursive(CArray<std::string>& Container, const std::filesystem::directory_entry& Entry, const bool bRecursive)
{
    if (Entry.is_directory() && bRecursive)
    {
        for (const std::filesystem::directory_entry& CurrentEntry : fs::directory_iterator(Entry.path()))
        {
            GetFilesFromDirectoryRecursive(Container, CurrentEntry, bRecursive);
        }
    }
    else if (!Entry.is_directory())
    {
        Container.Push(Entry.path().relative_path().string());
    }
}
