// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"

class FAiTree;

/**
 * AI actions base class
 */
class FAiActionBase
{
public:
	FAiActionBase(FAiTree* InAiTree);

	/** @Returns ai tree */
	FAiTree* GetTree() const;

private:
	FAiTree* AiTree;

};
