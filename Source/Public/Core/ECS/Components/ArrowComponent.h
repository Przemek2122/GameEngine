// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ECS/Component.h"
#include "Interfaces/TransformInterface2D.h"

class UBaseTransformComponent;

/**
 * Component for displaying simple arrow
 */
class UArrowComponent : public UComponent, public ITransformChildInterface2D<int>
{
public:
	UArrowComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UArrowComponent() override = default;

	/** Begin UComponent */
	void BeginPlay() override;
	void Render() override;
	/** End UComponent */

	void SetOnlyVisibleInDebug(const bool bInOnlyVisibleInDebug);
	bool IsOnlyVisibleInDebug() const;

protected:
	bool IsDebug() const;

	void RenderArrow();

private:
	bool bOnlyVisibleInDebug;

	UBaseTransformComponent* RootTransformComponent;

};