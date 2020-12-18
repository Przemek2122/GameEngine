#pragma once
#include <string>

class UObject
{
public:
	UObject();
	virtual ~UObject();
	
	std::string GetObjectName() const;
	
};

