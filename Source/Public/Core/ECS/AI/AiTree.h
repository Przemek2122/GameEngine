// Created by Przemys³aw Wiewióra 2024

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
