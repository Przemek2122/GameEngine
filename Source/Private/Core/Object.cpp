// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "Object.h"

FObject::FObject()
{
}

FObject::~FObject()
{
}

void FObject::Init()
{
}

std::string FObject::GetCppClassName() const
{
	return typeid(this).name();
}
