// Created by Przemys�aw Wiewi�ra 2024

#include "CoreEngine.h"
#include "Core/ECS/AI/AiTree.h"

FAiTree::FAiTree(EEntity* InOwnerEntity)
	: OwnerEntity(InOwnerEntity)
{
}

EEntity* FAiTree::GetOwnerEntity() const
{
	return OwnerEntity;
}
