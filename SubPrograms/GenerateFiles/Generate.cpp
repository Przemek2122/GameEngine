//

#define _CRT_SECURE_NO_WARNINGS

#include "Generate.h"
#include "GenerateFiles.h"
#include "GenerateFilters.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "Utilis.h"

int main(int Argc, char* Argv[])
{	
	std::cout << "Waiting for a click\n";
	std::cin.ignore();

	while (Argc--)
	{
		if (Argc == 0 && LaunchPath.empty())
		{
			LaunchPath = Argv[Argc];
		}
		else if (Argc == 1)
		{
			LaunchPath = Argv[Argc];
		}
		else if (Argc == 2)
		{
			ProjectName = Argv[Argc];
		}
    }
	
	{
		const int FindIndex = LaunchPath.find("SubPrograms");
		if (FindIndex == -1)
		{
			ProjectPath = LaunchPath.find("Scripts");
		}

		if (FindIndex != -1)
		{
			ProjectPath = LaunchPath.substr(0, FindIndex);
		}
		else
		{
			ProjectPath = LaunchPath;
		}
		
		SourcePath = ProjectPath + CodeDirectory;

		VcxprojFilePath				= ProjectPath + ProjectName + ".vcxproj";
		VcxprojFileBackupPath		= ProjectPath + ProjectName + ".vcxproj.backup";

		FilterFilePath				= ProjectPath + ProjectName + ".vcxproj.filters";
		FilterFileBackupPath		= ProjectPath + ProjectName + ".vcxproj.filters.backup";
	}

	// Get precompiled headers
	{
	    std::cout << " > Indexing files ..." << std::endl;
	
		for (const auto & File : std::filesystem::recursive_directory_iterator(SourcePath))
		{
    		const std::string FilePath = File.path().string();
    		const std::string FileLocalPath = FilePath.substr(FilePath.find(CodeDirectory) + CodeDirectory.length() + 1, FilePath.length());
			const std::string FileNameWithExt = FUtilis::GetFileFromPath(FilePath);
			const std::string FileExtension = FUtilis::GetFileExtension(FilePath);

			if (FileExtension == ".cpp")
			{
				CompileFiles.push_back(FileLocalPath);
			}
			else if (FileExtension == ".h")
			{
				IncludeFiles.push_back(FileLocalPath);
			}
			else if (FileExtension == ".hpp")
			{
				IncludeFiles.push_back(FileLocalPath);
			}
			else if (FileExtension == ".c")
			{
				CompileFiles.push_back(FileLocalPath);
			}
			else if (FileExtension == ".inl")
			{
				IncludeFiles.push_back(FileLocalPath);
			}
			else if (!FUtilis::HasProperExtension(FileLocalPath) && FUtilis::IsDirectory(FilePath))
			{
				Directories.push_back(FileLocalPath);
			}
		}
		
	    std::cout << " > " << IncludeFiles.size() << " .cpp files to include found." << std::endl;		
	    std::cout << " > " << CompileFiles.size() << " .h files to compile found." << std::endl;		
	}

	FGenerateFiles GenerateFiles;
	FGenerateFilters GenerateFilters;
}
