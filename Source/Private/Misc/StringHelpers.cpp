// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "Misc/StringHelpers.h"

bool FStringHelpers::CompareStringCaseInsensitive(const std::string& A, const std::string& B)
{
    return A.size() == B.size() && std::equal(A.begin(), A.end(), B.begin(), CompareCharsCaseInsensitive);
}

bool FStringHelpers::CompareCharsCaseInsensitive(const char A, const char B)
{
    return ( std::tolower(static_cast<unsigned char>(A)) == std::tolower(static_cast<unsigned char>(B)) );
}