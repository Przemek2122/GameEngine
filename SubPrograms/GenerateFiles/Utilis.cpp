//

#include "Utilis.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "Generate.h"

static std::vector<char> RandomChars = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8' , '9' };

bool FUtilis::HasProperExtension(const std::string& PathFile)
{
	const int DotIndex = PathFile.find('.');
	if (DotIndex != -1)
	{
		const std::string PathFileExtension = PathFile.substr(DotIndex + 1, PathFile.length());

		for (const std::string& FileExt : FilesExtensions)
		{
			if (FileExt == PathFileExtension)
			{
				return true;
			}
		}	
	}
	
	return false;
}

bool FUtilis::IsDirectory(const std::string& InPath)
{
	std::error_code ec;
	return std::filesystem::is_directory(InPath, ec);
}

int FUtilis::RandomTo(const int Max)
{
	// 0 to max
	return  (rand() % Max);
}

char FUtilis::GetRandomChar()
{
	return RandomChars[RandomTo(RandomChars.size())];
}

std::string FUtilis::GetRandomUniqueIdentifier()
{
	std::string Final;

	for (int i = 0; i < 8; i++)
	{
		Final += GetRandomChar();
	}

	Final += "-";
	
	for (int i = 0; i < 5; i++)
	{
		Final += GetRandomChar();
	}

	Final += "-";
	
	for (int i = 0; i < 5; i++)
	{
		Final += GetRandomChar();
	}
	
	Final += "-";
	
	for (int i = 0; i < 5; i++)
	{
		Final += GetRandomChar();
	}
	
	Final += "-";
	
	for (int i = 0; i < 12; i++)
	{
		Final += GetRandomChar();
	}

	return Final;
}

std::string FUtilis::GetPathWithOutFile(const std::string& InPath, int& WasFound)
{
	WasFound = InPath.find_last_of(GetPlatformSlash());

	if (WasFound != -1)
	{
		return InPath.substr(0, WasFound);
	}

	return "";
}

char FUtilis::GetPlatformSlash()
{
#if _WIN32 || _WIN64
	return '\\';
#else
	return '/';
#endif
}

void FUtilis::EraseAllSubStr(std::string& mainStr, const std::string& toErase)
{
	size_t StringIndexPosition = std::string::npos;
	// Search for the substring in string in a loop untill nothing is found
	bool Continue = true;
	while (Continue)
	{
		StringIndexPosition = mainStr.find(toErase);
		if (StringIndexPosition != std::string::npos)
		{
			mainStr.erase(StringIndexPosition, toErase.length());	
		}
		else
		{
			Continue = false;
		}
	}
}

long long int FUtilis::GetNumOfLinesInFile(const std::string& FilePath)
{
	std::ifstream InFile(FilePath);
	
	const long long int NumOfLines = std::count(
		std::istreambuf_iterator<char>(InFile), 
		std::istreambuf_iterator<char>(), '\n'
	);
	
	InFile.close();

	return NumOfLines;
}

void FUtilis::ConditionalBackupRecover(const std::string& FileOriginal, const std::string& FileBackup)
{
	long long int NumOfLines = FUtilis::GetNumOfLinesInFile(FileOriginal);

	// Backup
	if (NumOfLines > 100)
	{
		std::cout << " > Backup file '" << FileOriginal << "' ..." << std::endl;
	
		std::ifstream CopySource		(FileOriginal,		std::ios::binary);
		std::ofstream CopyDestination	(FileBackup,		std::ios::binary);

		CopyDestination << CopySource.rdbuf();
	}
	// Recover
	else
	{
		std::cout << " > Recover To '" << FileOriginal << "' ..." << " Due to " << NumOfLines << " in file." << std::endl;
		std::cout << " > Recover From '" << FileBackup << "' ..." << std::endl;

		std::ifstream CopySource		(FileBackup,		std::ios::binary);
		std::ofstream CopyDestination	(FileOriginal,		std::ios::binary);

		CopyDestination << CopySource.rdbuf();
	}
}
