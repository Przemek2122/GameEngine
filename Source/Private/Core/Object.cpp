//

#include "CoreEngine.h"
#include "Object.h"

UObject::UObject()
{
}

UObject::~UObject()
{
}

std::string UObject::GetObjectName() const
{
	return typeid(this).name();
}
