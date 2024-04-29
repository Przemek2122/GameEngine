// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"

class FStringHelpers
{
public:
	static bool CompareStringCaseInsensitive(const std::string& A, const std::string& B);
	static bool CompareCharsCaseInsensitive(char A, char B);

};
