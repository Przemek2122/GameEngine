// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "Core/ECS/AI/AiActionBase.h"

FAiActionBase::FAiActionBase(FAiTree* InAiTree)
	: AiTree(InAiTree)
{
}

FAiTree* FAiActionBase::GetTree() const
{
	return AiTree;
}
