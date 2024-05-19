// Created by Przemys³aw Wiewióra 2024

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

	/** Ticks only when action is active */
	void Tick();

	/** Called when parent tree chooses this action. */
	void StartAction();

	void EndAction();
		
	/** @Returns ai tree */
	FAiTree* GetTree() const;

	/** Used by AiTree to decide if this action is available. */
	bool IsActionReady() const;

	/** Used by AiTree to found action with the highest priority if EChooseActionMethod::ByPriority is used. Bigger means higher priority. */
	int32_t GetActionPriority() const;

private:
	FAiTree* AiTree;

};
