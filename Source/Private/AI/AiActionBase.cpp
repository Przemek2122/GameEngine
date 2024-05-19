// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "Core/ECS/AI/AiActionBase.h"

FAiActionBase::FAiActionBase(FAiTree* InAiTree)
	: AiTree(InAiTree)
{
}

void FAiActionBase::Tick()
{
}

void FAiActionBase::StartAction()
{
}

void FAiActionBase::EndAction()
{
}

FAiTree* FAiActionBase::GetTree() const
{
	return AiTree;
}

bool FAiActionBase::IsActionReady() const
{
	return true;
}

int32_t FAiActionBase::GetActionPriority() const
{
	return 0;
}
