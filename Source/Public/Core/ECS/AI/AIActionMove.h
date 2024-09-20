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

	bool ShouldFinishAction() const override;

	void StartAction() override;
	void EndAction() override;

protected:
	UMoveComponent* CurrentMoveComponent;

};
