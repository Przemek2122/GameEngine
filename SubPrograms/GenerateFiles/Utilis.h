//

#pragma once
#include <string>

class FUtilis
{
public:
	static bool HasProperExtension(const std::string& PathFile);

	static bool IsDirectory(const std::string& InPath);

	static int RandomTo(const int Max);
	
	static char GetRandomChar();
	static std::string GetRandomUniqueIdentifier();

	static std::string GetPathWithOutFile(const std::string& InPath, int& WasFound);

	static std::string GetFileFromPath(const std::string& InPath);
	static std::string GetFileExtension(const std::string& InPathOrFile);

	static char GetPlatformSlash();

	static void EraseAllSubStr(std::string & mainStr, const std::string & toErase);

	static long long int GetNumOfLinesInFile(const std::string& FilePath);

	static void ConditionalBackupRecover(const std::string& FileOriginal, const std::string& FileBackup, const int NumOfLinesToRecover = 300);
};
