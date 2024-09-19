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

	FRenderer* Renderer = GetOwnerWindow()->GetRenderer();
	const FVector2D<int> CurrentRendererOffset = Renderer->GetRenderOffset();

	Widget->SetWidgetLocation(GetLocation() - CurrentRendererOffset);
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
