//

#pragma once

#include <string>
#include <vector>

// Extension to be used when generating
const std::vector<std::string> FilesExtensions		= { "h", "cpp", "hpp", "c", "inl" };
// Source files directory
const std::string CodeDirectory						= "Source";
// Name of project to get vcxproj and filters of vcxproj
inline std::string ProjectName						= "GameEngine";
// XML ItemGroup
const std::string ItemGroupName = "<ItemGroup>";

// Count from 0, group with code should have content like this 
// <ClInclude Include="Source\Public\Containers\Array.h" />
const int ItemGroup_Files							= 1;
const int ItemGroup_FilterPrecompiledHeaders		= 3; 

inline std::string LaunchPath;
inline std::string ProjectPath;
inline std::string SourcePath;
