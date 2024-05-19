// Created by Przemys³aw Wiewióra 2020-2024

#pragma once

#include "ECS/BaseComponent.h"

class URenderComponent;

/**
 * Component for managing health
 * + Damage, healing, death with delegate
 */
class UHealthComponent : public UBaseComponent
{
public:
	UHealthComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UHealthComponent() override = default;

	/** Begin UBaseComponent */
	void BeginPlay() override;
	/** End UBaseComponent */

	virtual void TakeDamage(const float Damage);
	virtual void Heal(const float HealthToAdd);

	void SetStartingHealth(const float NewHealth);

	bool IsDead() const;

	/** Called when receiving damage - each time with damage taken */
	FDelegate<void, float> OnHealthLowered;

	/** Called when healing */
	FDelegate<void, float> OnHealthGained;

	/** Called when health drops below 0 */
	FDelegate<> OnDeathDelegate;

protected:
	virtual void SetHealthDefaults();

	/** Called when killed (Health is 0 or below) */
	virtual void OnDie();

protected:
	/** Current health */
	float CurrentHealth;

	/** Health which was set before start */
	float StartingHealth;

	/** Max health - Used when healing */
	float MaxHealth;

	/** Is currently dead? */
	bool bIsDead;

	/** Should use another component (RenderComponent) for health bar display? */
	bool bUseHealthBarComponent;

	URenderComponent* HealthBarRenderComponent;

};
