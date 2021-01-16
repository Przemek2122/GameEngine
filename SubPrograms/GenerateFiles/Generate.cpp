//

#define _CRT_SECURE_NO_WARNINGS

#include "Generate.h"
#include "GenerateFiles.h"
#include "GenerateFilters.h"

#include <filesystem>

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
	}

	FGenerateFiles GenerateFiles;
	FGenerateFilters GenerateFilters;
	
}
