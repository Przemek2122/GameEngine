// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Misc/Filesystem.h"

namespace fs = std::filesystem;

bool FFileSystem::Directory::Exists(const std::string& InPath)
{
    return (std::filesystem::is_directory(InPath));
}

bool FFileSystem::Directory::Create(const std::string& InPath)
{
	return fs::create_directory(InPath);
}

bool FFileSystem::Directory::Delete(const std::string& InPath, const bool bRecursive)
{
    if (bRecursive)
    {
        return fs::remove_all(InPath);
    }
    else
    {
        return fs::remove(InPath) != false;
    }
}

bool FFileSystem::File::Exists(const std::string& InPath)
{
    const std::ifstream FileCheck(InPath.c_str());

    return FileCheck.good();
}

bool FFileSystem::File::Create(const std::string& InPath)
{
	const std::ofstream File(InPath.c_str());

	return File.good();
}

bool FFileSystem::File::Delete(const std::string& InPath)
{
	return fs::remove(InPath);
}

bool FFileSystem::IsDirectory(const std::string& InPath)
{
	return fs::is_directory(InPath);
}

CArray<std::string> FFileSystem::GetFilesFromDirectory(const std::string& Path, const bool bRecursive)
{
    CArray<std::string> Files;

    for (const std::filesystem::directory_entry& Entry : fs::directory_iterator(Path))
    {
        GetFilesFromDirectoryRecursive(Files, Entry, bRecursive);
    }

    return Files;
}

CArray<std::string> FFileSystem::GetDirectories(const std::string& Path, const bool bCovertToJustFolders)
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

char FFileSystem::GetPlatformSlash()
{
    static char* PlatformSlash =
#if _WIN32 || _WIN64
	TEXT_CHAR("\\");
#else
    TEXT_CHAR("/");
#endif

	return *PlatformSlash;
}

char FFileSystem::GetPlatformEndLine()
{
	// This should be refactored to use the real platform end line not just windows hardcoded
	static char* PlatformEndLine = TEXT_CHAR("\n");

	return *PlatformEndLine;
}

void FFileSystem::GetFilesFromDirectoryRecursive(CArray<std::string>& Container, const std::filesystem::directory_entry& Entry, const bool bRecursive)
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
