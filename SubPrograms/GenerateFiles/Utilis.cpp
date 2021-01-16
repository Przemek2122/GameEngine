//

#include "Utilis.h"

#include <filesystem>

#include "Generate.h"

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
