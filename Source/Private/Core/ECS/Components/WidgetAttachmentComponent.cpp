#include "CoreEngine.h"
#include "ECS/Components/WidgetAttachmentComponent.h"

UWidgetAttachmentComponent::UWidgetAttachmentComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UComponent(InComponentManagerInterface)
	, Widget(nullptr)
{
}

void UWidgetAttachmentComponent::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Widget->SetWidgetLocation(GetLocation());
}

void UWidgetAttachmentComponent::SetWidget(FWidget* NewWidget)
{
	if (NewWidget != nullptr)
	{
		Widget = NewWidget;

		NewWidget->SetWidgetLocation(GetLocation());
		NewWidget->SetWidgetSize(GetSize());
	}
}

bool UWidgetAttachmentComponent::IsWidgetVisible() const
{
	return (Widget != nullptr && Widget->IsVisible());
}