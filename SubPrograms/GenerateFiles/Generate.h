//

#pragma once

#include <string>
#include <vector>

// Extension to be used when generating
const std::vector<std::string> FilesExtensions			= { "h", "cpp", "hpp", "c", "inl" };
// Source files directory
const std::string CodeDirectory							= "Source";
// Name of project to get vcxproj and filters of vcxproj
inline std::string ProjectName							= "GameEngine";
// XML ItemGroup
const std::string ItemGroupName = "<ItemGroup>";

const std::vector<std::string> SolutionConfigurations	= { "Debug", "Release" };
const std::vector<std::string> SolutionPlatforms	= { "x86", "x64", "ARM" };

const int ItemGroup_Files_Include 		= 1;
const int ItemGroup_Files_Compile		= 2;

inline bool IsDebugEnabled = true;

inline std::string VcxprojFilePath;
inline std::string VcxprojFileBackupPath;
inline std::string FilterFilePath;
inline std::string FilterFileBackupPath;

const std::string PreCompiledEngine = "CoreEngine";
inline std::vector<std::string> HeaderFiles;
inline std::vector<std::string> CppFiles;
inline std::vector<std::string> InlFiles;
inline std::vector<std::string> HppFiles;
inline std::vector<std::string> CFiles;

inline std::vector<std::string> Directories;

inline std::vector<std::string> IncludeFiles;
inline std::vector<std::string> CompileFiles;

inline std::string LaunchPath;
inline std::string ProjectPath;
inline std::string SourcePath;
