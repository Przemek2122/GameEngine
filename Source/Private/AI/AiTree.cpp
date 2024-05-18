// Created by Przemys³aw Wiewióra 2024

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
