// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"

/**
 * AI actions tree
 */
class FAiTree
{
public:
	FAiTree(EEntity* InOwnerEntity);

	EEntity* GetOwnerEntity() const;

private:
	EEntity* OwnerEntity;

};
