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
	std::cout << " > Generating filters ..." << std::endl;

	// Backup or recover
	FUtilis::ConditionalBackupRecover(FilterFilePath, FilterFileBackupPath);

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

	    	for (const std::string Directory : Directories)
	    	{
	    		std::cout << "Filter - add dir: " << Directory << std::endl;

    			FilterFile << "    <Filter Include=\"" << Directory + "\">" << std::endl;
				FilterFile << "      <UniqueIdentifier>{" << FUtilis::GetRandomUniqueIdentifier() << "}</UniqueIdentifier>" << std::endl;
				FilterFile << "    </Filter>" << std::endl;
	    	}
	    	
			FilterFile << "  </ItemGroup>" << std::endl;
	    	
			std::cout << " > Filter groups generated." << std::endl;
		}

		// Filter files include
		{
			FilterFile << "  <ItemGroup>" << std::endl;

			for (const std::string& IncludeFile : IncludeFiles)
			{
				if (IsDebugEnabled)
				{
    				std::cout << "Filter - add (include): " << IncludeFile << std::endl;
				}

				int WasFound;
				std::string ResultPath = FUtilis::GetPathWithOutFile(IncludeFile, WasFound);
				
				FilterFile << "    <ClInclude Include=\"" << CodeDirectory + "\\" << IncludeFile + "\">" << std::endl;
				FilterFile << "      <Filter>" << ResultPath + "</Filter>" << std::endl;
				FilterFile << "    </ClInclude>" << std::endl;
			}	
						
			FilterFile << "  </ItemGroup>" << std::endl;
	    	
			std::cout << " > Filter include generated." << std::endl;
		}
		
		// Filter files compile
		{
			FilterFile << "  <ItemGroup>" << std::endl;

			for (const std::string& CompileFile : CompileFiles)
			{
				if (IsDebugEnabled)
				{
    				std::cout << "Filter - add (compile): " << CompileFile << std::endl;
				}
				
				int WasFound;
				std::string ResultPath = FUtilis::GetPathWithOutFile(CompileFile, WasFound);
				
				if (WasFound)
				{
					FilterFile << "    <ClCompile Include=\"" << CodeDirectory + "\\" << CompileFile + "\">" << std::endl;
					FilterFile << "      <Filter>" << ResultPath + "</Filter>" << std::endl;
					FilterFile << "    </ClCompile>" << std::endl;		
				}
				else
				{
					std::cout << "Missing file? Maybe it has no extension? File: " << CompileFile << std::endl;
				}
			}
			
			FilterFile << "  </ItemGroup>" << std::endl;
		}

		FilterFile << FilterFileEndData;

		FilterFile.close();
		
	    std::cout << " > Filter compile generated." << std::endl;		
	}
	
	std::cout << " > Generated filters" << std::endl;
}

FGenerateFilters::~FGenerateFilters()
{
}
