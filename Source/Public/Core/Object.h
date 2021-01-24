// Created by Przemys³aw Wiewióra 2020

#pragma once
#include <string>

class UObject
{
public:
	UObject();
	virtual ~UObject();
	
	std::string GetObjectName() const;
	
};

