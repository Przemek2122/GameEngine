// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "ECS/Components/HealthComponent.h"
#include "ECS/Components/RenderComponent.h"
#include "Misc/Math.h"

UHealthComponent::UHealthComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UBaseComponent(InComponentManagerInterface)
	, CurrentHealth(100.f)
	, StartingHealth(100.f)
	, MaxHealth(100.f)
	, bIsDead(false)
	, bUseHealthBarComponent(false)
	, HealthBarRenderComponent(nullptr)
{
}

void UHealthComponent::BeginPlay()
{
	UBaseComponent::BeginPlay();

	SetHealthDefaults();

	if (bUseHealthBarComponent)
	{
		HealthBarRenderComponent = CreateComponent<URenderComponent>("HealthBarRenderComponent");
	}
}

void UHealthComponent::SetHealthDefaults()
{
	CurrentHealth = StartingHealth;
}

void UHealthComponent::TakeDamage(const float Damage)
{
	CurrentHealth -= FMath::Abs(Damage);

	OnHealthLowered.Execute(Damage);

	if (CurrentHealth <= 0.f)
	{
		OnDie();
	}
}

void UHealthComponent::Heal(const float HealthToAdd)
{
	CurrentHealth += FMath::Abs(HealthToAdd);

	OnHealthGained.Execute(HealthToAdd);

	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

void UHealthComponent::SetStartingHealth(const float NewHealth)
{
	StartingHealth = NewHealth;
	CurrentHealth = NewHealth;
}

bool UHealthComponent::IsDead() const
{
	return bIsDead;
}

void UHealthComponent::OnDie()
{
	CurrentHealth = 0.f;

	bIsDead = true;

	OnDeathDelegate.Execute();
}
