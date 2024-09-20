// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"

class FAITree;

/**
 * AI actions base class
 */
class FAIActionBase
{
public:
	FAIActionBase(FAITree* InAiTree);
	virtual ~FAIActionBase() = default;

	/** Ticks only when action is active */
	virtual void Tick();

	/** Called when parent tree chooses this action. */
	void Start();

	/** Call to end action */
	void End();

	/** used by AiTree to check if action should be finished */
	virtual bool ShouldFinishAction() const;

	/** Used by AiTree to decide if this action is available. */
	virtual bool IsActionReady() const;

	/** Used by AiTree to found action with the highest priority if EChooseActionMethod::ByPriority is used. Bigger means higher priority. */
	virtual int32_t GetActionPriority() const;

	/** @return owner AI tree */
	FAITree* GetTree() const;

	/** @return Entity owner for this action */
	EEntity* GetEntity() const;

protected:
	virtual void StartAction();
	virtual void EndAction();

private:
	FAITree* AiTree;

};
