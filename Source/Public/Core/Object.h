// Created by Przemys³aw Wiewióra 2020

#pragma once
#include <string>

class UObject
{
public:
	UObject();
	virtual ~UObject();

	virtual void Init();
	
	_NODISCARD std::string GetObjectName() const;
	
};
