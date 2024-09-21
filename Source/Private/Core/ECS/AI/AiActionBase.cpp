// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "Core/ECS/AI/AIActionBase.h"

FAIActionBase::FAIActionBase(FAITree* InAiTree)
	: AiTree(InAiTree)
{
}

void FAIActionBase::Initialize()
{
}

void FAIActionBase::Tick()
{
}

void FAIActionBase::Start()
{
	StartAction();
}

void FAIActionBase::End()
{
	EndAction();
}

bool FAIActionBase::ShouldFinishAction() const
{
	return false;
}

bool FAIActionBase::IsActionReady() const
{
	return true;
}

int32_t FAIActionBase::GetActionPriority() const
{
	return 0;
}

FAITree* FAIActionBase::GetTree() const
{
	return AiTree;
}

EEntity* FAIActionBase::GetEntity() const
{
	return AiTree->GetOwnerEntity();
}

void FAIActionBase::StartAction()
{
}

void FAIActionBase::EndAction()
{
}
