// Created by Przemys³aw Wiewióra 2020-2024

#include "CoreEngine.h"
#include "Core/ECS/Components/SquareCollisionComponent.h"

#include "ECS/Collision/SquareCollision.h"

USquareCollisionComponent::USquareCollisionComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UCollisionComponent(InComponentManagerInterface)
	, SquareCollision(nullptr)
{
}

USquareCollisionComponent::~USquareCollisionComponent()
{
	delete SquareCollision;
}

void USquareCollisionComponent::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

#if _DEBUG
	// Draw collision
	if (SquareCollision != nullptr)
	{
		FRenderer* Renderer = GetOwnerWindow()->GetRenderer();

		const FSquareData& SquareData = SquareCollision->GetSquareData();

		Renderer->DrawRectangleOutline(SquareData.GetLocation(), SquareData.GetSize(), GetCollisionDebugColor());
	}
#endif
}

void USquareCollisionComponent::Init()
{
	Super::Init();

	SquareCollision = new FSquareCollision(GetLocationUser(), GetSize());

	AddCollision(SquareCollision);
}
