//

#include "GenerateFilters.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include "Generate.h"
#include "Utilis.h"

static std::string FilterFileBeginData = "<?xml version=\"1.0\" encoding=\"utf-8\"?> \n<Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">";
static std::string FilterFileEndData = "  <ItemGroup>\n    <None Include=\"cpp.hint\" /> \n  </ItemGroup> \n</Project> \n";

FGenerateFilters::FGenerateFilters()
{
	const std::string FilterFilePath			= ProjectPath + ProjectName + ".vcxproj.filters";
	const std::string FilterFileBackupPath		= ProjectPath + ProjectName + ".vcxproj.filters.backup";

	std::cout << " > Generating filters ..." << std::endl;

	// Backup file
	FUtilis::ConditionalBackupRecover(FilterFilePath, FilterFileBackupPath);

	std::vector<std::string> PrecompiledHeaders;
	
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

	// Clean file
	{
		std::cout << " > Clean old file ..." << std::endl;
		
		std::ofstream CleanOfStream;
		CleanOfStream.open(FilterFilePath, std::ofstream::out | std::ofstream::trunc);
		CleanOfStream.close();
	}
	
	// Generate
	{
	    std::cout << " > Starting generating filters ..." << std::endl;

		std::ofstream FilterFile(FilterFilePath, std::ios_base::app | std::ios_base::out);

		int CurrentItemGroup = 0;
		bool bGroupBegin = false;

		FilterFile << FilterFileBeginData;

		// Filters
		{
			FilterFile << "  <ItemGroup>" << std::endl;
						
			for (const auto & File : std::filesystem::recursive_directory_iterator(SourcePath))
			{
    			const std::string FilePath = File.path().string();
    			const std::string FileLocalPath = FilePath.substr(FilePath.find(CodeDirectory) + CodeDirectory.length() + 1, FilePath.length());

    			if (!FUtilis::HasProperExtension(FileLocalPath) && FUtilis::IsDirectory(FilePath))
				{
					std::cout << "Filter - add dir: " << FileLocalPath << std::endl;

    				FilterFile << "    <Filter Include=\"" << FileLocalPath + "\">" << std::endl;
					FilterFile << "      <UniqueIdentifier>{" << FUtilis::GetRandomUniqueIdentifier() << "}</UniqueIdentifier>" << std::endl;
					FilterFile << "    </Filter>" << std::endl;
				}
			}

			FilterFile << "  </ItemGroup>" << std::endl;
		}

		// Filter files
		{
			FilterFile << "  <ItemGroup>" << std::endl;

			for (const auto & File : std::filesystem::recursive_directory_iterator(SourcePath))
			{
				const std::string FilePath = File.path().string();
    			const std::string FileLocalPath = FilePath.substr(FilePath.find(CodeDirectory) + CodeDirectory.length() + 1, FilePath.length());

				bool bContains = false;

				for (std::string& PrecompiledHeader : PrecompiledHeaders)
				{
					if (PrecompiledHeader == FileLocalPath)
					{
						bContains = true;
					}
				}

				if (!bContains)
				{
					int WasFound;
					std::string ResultPath = FUtilis::GetPathWithOutFile(FileLocalPath, WasFound);

					if (WasFound != -1)
					{
						FilterFile << "    <ClInclude Include=\"" << FileLocalPath + "\">" << std::endl;
						FilterFile << "      <Filter>" << ResultPath + "</Filter>" << std::endl;
						FilterFile << "    </ClInclude>" << std::endl;	
					}	
				}
			}
						
			FilterFile << "  </ItemGroup>" << std::endl;
		}

		// Precompiled headers
		{
			FilterFile << "  <ItemGroup>" << std::endl;

			for (std::string& PrecompiledHeader : PrecompiledHeaders)
			{
				int WasFound;
				std::string ResultPath = FUtilis::GetPathWithOutFile(PrecompiledHeader, WasFound);
							
				FilterFile << "    <ClCompile Include=\"" << CodeDirectory + "\\" << PrecompiledHeader + "\">" << std::endl;
				FilterFile << "      <Filter>" << ResultPath + "</Filter>" << std::endl;
				FilterFile << "    </ClCompile>" << std::endl;	
			}
					
			FilterFile << "  </ItemGroup>" << std::endl;
		}

		FilterFile << FilterFileEndData;

		FilterFile.close();
		
	    std::cout << " > Filters generated." << std::endl;		
	}
	
	std::cout << " > Generated filters" << std::endl;
}

FGenerateFilters::~FGenerateFilters()
{
}
