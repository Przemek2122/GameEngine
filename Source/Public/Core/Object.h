// Created by Przemys³aw Wiewióra 2020

#pragma once
#include <string>

class FObject
{
public:
	FObject();
	virtual ~FObject();

	virtual void Init();
	
	_NODISCARD std::string GetCppClassName() const;
	
};
