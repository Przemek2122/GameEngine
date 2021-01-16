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

// Count from 0, group with code should have content like this 
// <ClInclude Include="Source\Public\Containers\Array.h" />
const int ItemGroup_Files							= 1;
// Count from 0, group with code should have content like this
// <Filter Include="Source\Public\Core">
//   <UniqueIdentifier>{0f473372-0a89-42d1-9ed5-3c40a839e3af}</UniqueIdentifier>
//  </Filter>
const int ItemGroup_Filters							= 0; 

inline std::string LaunchPath;
inline std::string ProjectPath;
inline std::string SourcePath;
