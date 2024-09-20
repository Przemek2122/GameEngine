// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "AIActionBase.h"

class UMoveComponent;
class FAITree;

/**
 * AI actions base class
 */
class FAIActionMove : public FAIActionBase
{
public:
	FAIActionMove(FAITree* InAiTree);
	virtual ~FAIActionMove() override = default;

	/** Begin FAIActionBase */
	void Initalize() override;
	bool ShouldFinishAction() const override;
	bool IsActionReady() const override;

	void StartAction() override;
	void EndAction() override;
	/** End FAIActionBase */

protected:
	UMoveComponent* CurrentMoveComponent;

};
