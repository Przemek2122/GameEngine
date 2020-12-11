//

#pragma once

#include "CoreMinimal.h"

class FFilesystem
{
public:
	static bool CreateDirrectory(const std::string Path);

	static bool DeleteDirrectory(const std::string Path, const bool bRecursive = false);

};
