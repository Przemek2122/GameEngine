// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Misc/Filesystem.h"

#include <filesystem>
namespace fs = std::filesystem;

bool FFilesystem::CreateDirrectory(const std::string Path)
{
    return fs::create_directory(Path);
}

bool FFilesystem::DeleteDirrectory(const std::string Path, const bool bRecursive)
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