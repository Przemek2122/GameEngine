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
	while (Argc--)
	{
		if (Argc == 0)
		{
			LaunchPath = Argv[Argc];
		}
		// Custom path
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
	    std::cout << " > Searching for pre compiled headers ..." << std::endl;
	
		std::ifstream FilterFileBackupRead(FilterFileBackupPath.c_str());
		std::string FilterFileBackupLine;

		int CurrentItemGroup = 0;
		
		const std::string FirstPartClCompile = "<ClCompile Include=\"";
		const std::string LastPartClCompile = "\">";
		const std::string ToErase = CodeDirectory + "\\";
		
		while (std::getline(FilterFileBackupRead, FilterFileBackupLine)) 
		{
			if (FilterFileBackupLine.find(ItemGroupName) != std::string::npos)
			{
				CurrentItemGroup++;
			}

			if (CurrentItemGroup == ItemGroup_FilterPrecompiledHeaders)
			{
				const int ItemIndex = FilterFileBackupLine.find(FirstPartClCompile);
				
				if (ItemIndex != -1)
				{
					std::string PrecompiledHeaderLine = FilterFileBackupLine.substr(ItemIndex + FirstPartClCompile.length(), FilterFileBackupLine.length());

					PrecompiledHeaderLine = PrecompiledHeaderLine.substr(0, PrecompiledHeaderLine.find(LastPartClCompile));
					
					FUtilis::EraseAllSubStr(PrecompiledHeaderLine, ToErase);
					
					PrecompiledHeaders.emplace_back(PrecompiledHeaderLine);
				}
			}
		}
	
		FilterFileBackupRead.close();
		
	    std::cout << " > " << PrecompiledHeaders.size() << " Precompiled headers found." << std::endl;		
	}

	FGenerateFiles GenerateFiles;
	FGenerateFilters GenerateFilters;
}
