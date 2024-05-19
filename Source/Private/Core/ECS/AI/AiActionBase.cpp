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

void FAiActionBase::Start()
{
	StartAction();
}

void FAiActionBase::End()
{
	EndAction();
}

bool FAiActionBase::ShouldFinishAction() const
{
	return false;
}

bool FAiActionBase::IsActionReady() const
{
	return true;
}

int32_t FAiActionBase::GetActionPriority() const
{
	return 0;
}

FAiTree* FAiActionBase::GetTree() const
{
	return AiTree;
}

EEntity* FAiActionBase::GetEntity() const
{
	return AiTree->GetOwnerEntity();
}

void FAiActionBase::StartAction()
{
}

void FAiActionBase::EndAction()
{
}
