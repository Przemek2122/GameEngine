//

#include "GenerateFilters.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Generate.h"
#include "Utilis.h"

FGenerateFilters::FGenerateFilters()
{
	const std::string FilterFilePath			= ProjectPath + ProjectName + ".vcxproj.filters";
	const std::string FilterFileBackupPath		= ProjectPath + ProjectName + ".vcxproj.filters.backup";

	std::cout << " > Generating filters ..." << std::endl;

	// Backup file
	{
		std::cout << " > Backup file '" << FilterFilePath << "' ..." << std::endl;
		
		std::ifstream CopySource		(FilterFilePath,			std::ios::binary);
	    std::ofstream CopyDestination	(FilterFileBackupPath,		std::ios::binary);

	    CopyDestination << CopySource.rdbuf();
	}

	// Clear file
	{
		std::cout << " > Clean old file ..." << std::endl;
		
		std::ofstream CleanOfStream;
		CleanOfStream.open(FilterFilePath, std::ofstream::out | std::ofstream::trunc);
		CleanOfStream.close();
	}

	// Generate
	{
	    std::cout << " > Starting generating files ..." << std::endl;

		std::ofstream FilterFile(FilterFilePath, std::ios_base::app | std::ios_base::out);

		std::ifstream FilterFileBackup(FilterFileBackupPath.c_str());
		std::string FilterFileBackupLine;

		int CurrentItemGroup = 0;
		bool bGroupStart = false;

		const std::string ItemGroupName = "<ItemGroup>";
		
		while (std::getline(FilterFileBackup, FilterFileBackupLine)) 
		{
			if (FilterFileBackupLine.find(ItemGroupName) != std::string::npos)
			{
				CurrentItemGroup++;
				bGroupStart = true;
			}

			if (CurrentItemGroup == ItemGroup_Files)
			{
				if (bGroupStart)
				{
					FilterFile << "  <ItemGroup>" << std::endl;
					
					for (const auto & File : std::filesystem::recursive_directory_iterator(SourcePath))
				    {
    					const std::string FilePath = File.path().string();
    					const std::string FileLocalPath = FilePath.substr(FilePath.find(CodeDirectory) + CodeDirectory.length() + 1, FilePath.length());

    					if (FUtilis::HasProperExtension(FileLocalPath))
						{
							std::cout << "Filter - add: " << FileLocalPath << std::endl;

    						FilterFile << "    <ClInclude Include=\"" << FileLocalPath << "\" />" << std::endl;
						}
						else
						{
							if (FUtilis::IsDirectory(FilePath))
							{
								std::cout << "Filter - Found directory: " << FileLocalPath << std::endl;	
							}
							else
							{
								std::cout << "Filter - Ignored: " << FileLocalPath << std::endl;	
							}
						}
					}

					FilterFile << "  </ItemGroup>" << std::endl;
				}	
			}
			else
			{
				FilterFile << FilterFileBackupLine << std::endl;
			}

			bGroupStart = false;
		}

		FilterFile.close();
		FilterFileBackup.close();
		
	    std::cout << " > Files generated!" << std::endl;		
	}
	
	std::cout << " > Generated filters" << std::endl;
}

FGenerateFilters::~FGenerateFilters()
{
}
