#include "CoreEngine.h"
#include "Core/Test/TestClassType.h"

#if ENGINE_TESTS_ALLOW_ANY
void FTestClassType::DoTest()
{
	StoredClass.Reset();

	if (!StoredClass.IsSet())
	{
		LOG_DEBUG("Class NOT set after Reset.");
	}

	StoredClass.Set<float>();

	if (StoredClass.IsSet())
	{
		LOG_DEBUG("Class set");
	}

	if (StoredClass.IsSame<int>())
	{
		LOG_DEBUG("Class is int");
	}
	
	if (StoredClass.IsSame<float>())
	{
		LOG_DEBUG("Class is float");
	}

	StoredClass.Set<FTemporaryTestClass>();
	FTemporaryTestClass* ClassInstance = StoredClass.Allocate();

	if (ClassInstance != nullptr)
	{
		LOG_DEBUG("TemporaryTestClass instance created from class name: " << StoredClass.GetClassName());
	}

	delete ClassInstance;
}

#endif