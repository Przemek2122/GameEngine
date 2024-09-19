#pragma once

#include "ECS/Component.h"

/**
 * Component with attached component for display on entity
 */
class UWidgetAttachmentComponent : public UComponent
{
public:
	explicit UWidgetAttachmentComponent(IComponentManagerInterface* InComponentManagerInterface);

	/** Begin UBaseComponent */
	void Tick(const float DeltaTime) override;
	/** End UBaseComponent */

	/** Set managed widget for this component */
	void SetWidget(FWidget* NewWidget);

	/** Get widget of this component */
	FWidget* GetWidget() const { return Widget; }

	bool IsWidgetVisible() const;

protected:
	/** Managed widget for this component */
	FWidget* Widget;

};
