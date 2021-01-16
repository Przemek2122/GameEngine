//

#pragma once
#include <string>

class FUtilis
{
public:
	static bool HasProperExtension(const std::string& PathFile);

	static bool IsDirectory(const std::string& InPath);
};
