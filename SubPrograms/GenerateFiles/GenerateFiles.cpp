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
	// Backup or recover
	FUtilis::ConditionalBackupRecover(VcxprojFilePath, VcxprojFileBackupPath);

	// Clean file
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
		
		while (std::getline(VcxprojBackup, VcxprojBackupLine)) 
		{
			if (VcxprojBackupLine.find(ItemGroupName) != std::string::npos)
			{
				CurrentItemGroup++;
				bGroupStart = true;
			}

			switch (CurrentItemGroup)
			{
			case ItemGroup_Files_Include:
				{
					if (bGroupStart)
					{
						Vcxproj << "  <ItemGroup>" << std::endl;

						for (std::string& File : IncludeFiles)
						{
							// Skip if precompiled header
							if (File.find(PreCompiledEngine + ".h") != -1)
							{
								continue;
							}
							
							int SourceDirIndex = File.find(CodeDirectory);

							if (IsDebugEnabled)
							{
    							std::cout << "File - add (include): " << File << std::endl;
							}
    								
    						if (SourceDirIndex != -1)
    						{
    							Vcxproj << "    <ClInclude Include=\"" << File << "\" />" << std::endl;	
    						}
							else
							{
    							Vcxproj << "    <ClInclude Include=\"" << CodeDirectory + "\\" << File << "\" />" << std::endl;		
							}
						}

						Vcxproj << "  </ItemGroup>" << std::endl;
					}
					
					break;
				}

			case ItemGroup_Files_Compile:
				{
					if (bGroupStart)
					{
						Vcxproj << "  <ItemGroup>" << std::endl;

						if (IsDebugEnabled)
						{
    						std::cout << "File - add (Precompiled header): " << PreCompiledEngine << ".cpp/.h" << std::endl;
						}
						
						// Precompiled header
						{
							Vcxproj << "    <ClCompile Include=\"Source\\Private\\Core\\CoreEngine.cpp\">" << std::endl;
							for (const std::string& SolutionConfiguration : SolutionConfigurations)
							{
								for (const std::string& SolutionPlatform : SolutionPlatforms)
								{
									Vcxproj << "      <PrecompiledHeader Condition=\"'$(Configuration)|$(Platform)'=='" << SolutionConfiguration << "|" << SolutionPlatform << "'\">Create</PrecompiledHeader>" << std::endl;
									Vcxproj << "      <PrecompiledHeaderFile Condition=\"'$(Configuration)|$(Platform)'=='" << SolutionConfiguration << "|" << SolutionPlatform << "'\">" << PreCompiledEngine + ".h" << "</PrecompiledHeaderFile>" << std::endl;
								}
							}
							Vcxproj << "    </ClCompile>" << std::endl;
						}
							
						for (std::string& File : CompileFiles)
						{
							if (IsDebugEnabled)
							{
    							std::cout << "File - add (compile): " << File << std::endl;
							}

							// Skip if precompiled header
							if (File.find(PreCompiledEngine + ".cpp") != -1)
							{
								continue;
							}
							
							int SourceDirIndex = File.find(CodeDirectory);
    								
    						if (SourceDirIndex == -1)
							{
    							Vcxproj << "    <ClCompile Include=\"" << CodeDirectory + "\\" << File << "\" />" << std::endl;		
							}
							else
    						{
    							Vcxproj << "    <ClCompile Include=\"" << File << "\" />" << std::endl;	
    						}
						}

						Vcxproj << "  </ItemGroup>" << std::endl;
					}
					
					break;
				}

			default:
				{
					Vcxproj << VcxprojBackupLine << std::endl;
				}
			}

			/*
			if (CurrentItemGroup == ItemGroup_Files_Include)
			{
				if (bGroupStart)
				{
					Vcxproj << "  <ItemGroup>" << std::endl;

					for (std::string& File : IncludeFiles)
					{
						int SourceDirIndex = File.find(CodeDirectory);

						if (IsDebugEnabled)
						{
    						std::cout << "File - add (include): " << File << std::endl;
						}
    							
    					if (SourceDirIndex != -1)
    					{
    						Vcxproj << "    <ClInclude Include=\"" << File << "\" />" << std::endl;	
    					}
						else
						{
    						Vcxproj << "    <ClInclude Include=\"" << CodeDirectory + "\\" << File << "\" />" << std::endl;		
						}
					}

					Vcxproj << "  </ItemGroup>" << std::endl;
				}	
			}
			else if (CurrentItemGroup == ItemGroup_Files_Compile)
			{
				if (bGroupStart)
				{
					Vcxproj << "  <ItemGroup>" << std::endl;

					if (IsDebugEnabled)
					{
    					std::cout << "File - add (Precompiled header): " << PreCompiledEngineHeader << std::endl;
					}

					// Precompiled header
					{
						Vcxproj << "  <ClCompile Include=\"Source\\Private\\Core\\CoreEngine.cpp\">" << std::endl;
						for (const std::string& SolutionConfiguration : SolutionConfigurations)
						{
							for (const std::string& SolutionPlatform : SolutionPlatforms)
							{
								Vcxproj << "    <PrecompiledHeader Condition=\"'$(Configuration)|$(Platform)'=='" << SolutionConfiguration << "|" << SolutionPlatform << "'\">Create</PrecompiledHeader>" << std::endl;
								Vcxproj << "    <PrecompiledHeaderFile Condition=\"'$(Configuration)|$(Platform)'=='" << SolutionConfiguration << "|" << SolutionPlatform << "'\">" << PreCompiledEngineHeader << "</PrecompiledHeaderFile>" << std::endl;
							}
						}
						Vcxproj << "  </ClCompile>" << std::endl;
					}
						
					for (std::string& File : CompileFiles)
					{
						// Skip if precompiled header
						if (File.find(PreCompiledEngineHeader) != -1)
						{
							return;
						}

						if (IsDebugEnabled)
						{
    						std::cout << "File - add (compile): " << File << std::endl;
						}
						
						int SourceDirIndex = File.find(CodeDirectory);
    							
    					if (SourceDirIndex == -1)
						{
    						Vcxproj << "    <ClCompile Include=\"" << CodeDirectory + "\\" << File << "\" />" << std::endl;		
						}
						else
    					{
    						Vcxproj << "    <ClCompile Include=\"" << File << "\" />" << std::endl;	
    					}
					}

					Vcxproj << "  </ItemGroup>" << std::endl;
				}
			}
			else
			{
				Vcxproj << VcxprojBackupLine << std::endl;
			}
			*/

			bGroupStart = false;
		}

		Vcxproj.close();
		VcxprojBackup.close();
		
	    std::cout << " > Files generated." << std::endl;		
	}
}

FGenerateFiles::~FGenerateFiles()
{
}
