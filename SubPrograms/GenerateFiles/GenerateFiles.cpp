//

#include "GenerateFiles.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Generate.h"
#include "Utilis.h"

FGenerateFiles::FGenerateFiles()
{
	const std::string VcxprojFilePath			= ProjectPath + ProjectName + ".vcxproj";
	const std::string VcxprojFileBackupPath		= ProjectPath + ProjectName + ".vcxproj.backup";

	// Backup file
	{
		std::cout << " > Backup file '" << VcxprojFilePath << "' ..." << std::endl;
		
		std::ifstream CopySource		(VcxprojFilePath,			std::ios::binary);
	    std::ofstream CopyDestination	(VcxprojFileBackupPath,		std::ios::binary);

	    CopyDestination << CopySource.rdbuf();
	}

	// Clear file
	{
		std::cout << " > Clean old file ..." << std::endl;
		
		std::ofstream CleanOfStream;
		CleanOfStream.open(VcxprojFilePath, std::ofstream::out | std::ofstream::trunc);
		CleanOfStream.close();
	}
	
	// Generate
	{
	    std::cout << " > Starting generating files ..." << std::endl;

		std::ofstream Vcxproj(VcxprojFilePath, std::ios_base::app | std::ios_base::out);

		std::ifstream VcxprojBackup(VcxprojFileBackupPath.c_str());
		std::string VcxprojBackupLine;

		int CurrentItemGroup = 0;
		bool bGroupStart = false;

		const std::string ItemGroupName = "<ItemGroup>";
		
		while (std::getline(VcxprojBackup, VcxprojBackupLine)) 
		{
			if (VcxprojBackupLine.find(ItemGroupName) != std::string::npos)
			{
				CurrentItemGroup++;
				bGroupStart = true;
			}

			if (CurrentItemGroup == ItemGroup_Files)
			{
				if (bGroupStart)
				{
					Vcxproj << "  <ItemGroup>" << std::endl;
					
					for (const auto & File : std::filesystem::recursive_directory_iterator(SourcePath))
				    {
    					const std::string FilePath = File.path().string();
    					const std::string FileLocalPath = FilePath.substr(FilePath.find(CodeDirectory) + CodeDirectory.length() + 1, FilePath.length());

    					if (FUtilis::HasProperExtension(FileLocalPath))
						{
							std::cout << "File - add: " << FileLocalPath << std::endl;

    						Vcxproj << "    <ClInclude Include=\"" << FileLocalPath << "\" />" << std::endl;
						}
						else
						{
							std::cout << "File - ignored: " << FileLocalPath << std::endl;	
						}
					}

					Vcxproj << "  </ItemGroup>" << std::endl;
				}	
			}
			else
			{
				Vcxproj << VcxprojBackupLine << std::endl;
			}

			bGroupStart = false;
		}

		Vcxproj.close();
		VcxprojBackup.close();
		
	    std::cout << " > Files generated!" << std::endl;		
	}
}

FGenerateFiles::~FGenerateFiles()
{
}
