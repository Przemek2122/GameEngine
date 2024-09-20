// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"
#include "AiActionBase.h"

class UMoveComponent;
class FAITree;

/**
 * AI actions base class
 */
class FAiActionMove : public FAiActionBase
{
public:
	FAiActionMove(FAITree* InAiTree);
	virtual ~FAiActionMove() override = default;

	bool ShouldFinishAction() const override;

	void StartAction() override;
	void EndAction() override;

protected:
	UMoveComponent* CurrentMoveComponent;

};
