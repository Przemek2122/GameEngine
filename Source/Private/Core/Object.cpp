// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "Object.h"

UObject::UObject()
{
}

UObject::~UObject()
{
}

void UObject::Init()
{
}

std::string UObject::GetCppClassName() const
{
	return typeid(this).name();
}
