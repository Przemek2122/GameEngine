// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "AiActionBase.h"

class UMoveComponent;
class FAiTree;

/**
 * AI actions base class
 */
class FAiActionMove : public FAiActionBase
{
public:
	FAiActionMove(FAiTree* InAiTree);
	virtual ~FAiActionMove() override = default;

	bool ShouldFinishAction() const override;

	void StartAction() override;
	void EndAction() override;

protected:
	UMoveComponent* CurrentMoveComponent;

};
