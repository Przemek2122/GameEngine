// Created by Przemys³aw Wiewióra 2020-2024

#pragma once

#include "CoreMinimal.h"

/** Storage class for storing TClass or FClassAllocateInterface */
class FCLass
{
public:
    virtual ~FCLass() = default;

    virtual void* Allocate() const = 0;
    virtual void* Cast(void* Object) const = 0;
};

template<typename T> class TClass : public FCLass
{
public:
	void* Allocate() const override { return new T; }
	void* Cast(void* Object) const override { return static_cast<T*>(Object); }
};

class FClassAllocateInterface
{
public:

};

/** Ussage sample */
FCLass* type = new TClass<int>;
void* myint = type->Allocate();
