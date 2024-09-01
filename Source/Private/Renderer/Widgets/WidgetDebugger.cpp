// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "Renderer/Widgets/WidgetDebugger.h"

#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"

FWidgetDebugger::FWidgetDebugger(FWindow* InWindow)
	: Window(InWindow)
	, DebuggerWindow(nullptr)
{
}

void FWidgetDebugger::StartDebugger()
{
	FWidgetManager* WidgetManager = Window->GetWidgetManager();
	if (WidgetManager != nullptr)
	{
		FWindowCreationData WindowCreationData(true);

		static const std::string ColonDebugger = " : Widget Debugger";
		const std::string WindowName = Window->GetWindowTitle() + ColonDebugger;

		static const FVector2D<int> WindowLocation = Window->GetWindowLocation() + FVector2D<int>(Window->GetWindowSize().X, 0);
		static const FVector2D<int> WindowDefaultSize = FVector2D<int>(800, 600);

		DebuggerWindow = GEngine->GetEngineRender()->CreateWindow<FWindow>(WindowCreationData, WindowName, WindowLocation, WindowDefaultSize);
		if (DebuggerWindow != nullptr)
		{
			// Refresh all widgets in debugger
			RefreshDisplayedWidgets();

			// Bind to refresh on each changed of widget
			WidgetManager->OnAnyWidgetChanged.BindObject(this, &FWidgetDebugger::RefreshDisplayedWidgets);
		}
	}
}

void FWidgetDebugger::RefreshDisplayedWidgets()
{
	FWidgetManager* WindowWidgetManager = Window->GetWidgetManager();
	FWidgetManager* DebuggerWindowWidgetManager = DebuggerWindow->GetWidgetManager();

	if (WindowWidgetManager != nullptr && DebuggerWindowWidgetManager != nullptr)
	{
		DebuggerWindowWidgetManager->ClearChildren();

		FVerticalBoxWidget* VerticalBox = DebuggerWindowWidgetManager->CreateWidget<FVerticalBoxWidget>();
		VerticalBox->SetWidgetSizePercent({ 1, 1 });

		CArray<FWidget*> Widgets = WindowWidgetManager->GetManagedWidgets();

		CreateDebuggersForWidgets(VerticalBox, Widgets, 0);
	}
}

void FWidgetDebugger::CreateDebuggersForWidgets(FVerticalBoxWidget* InVerticalBox, const CArray<FWidget*>& InWidgets, int32 Depth)
{
	static const std::string DepthString = "^";

	for (FWidget* Widget : InWidgets)
	{
		std::string WidgetDepthNote;
		const std::string WidgetName = Widget->GetName();

		if (Depth == 0)
		{
			// R means it's root due to 0 depth
			WidgetDepthNote = 'R';
		}
		else
		{
			for (int32 i = 0; i < Depth; i++)
			{
				WidgetDepthNote += DepthString;
			}
		}
		
		std::string FinalWidgetName = WidgetDepthNote;
		FinalWidgetName += " - ";
		FinalWidgetName += WidgetName;

		//FButtonWidget* Button = InVerticalBox->CreateWidget<FButtonWidget>();

		FTextWidget* TextWidget = InVerticalBox->CreateWidget<FTextWidget>();
		TextWidget->SetText(FinalWidgetName);

		CArray<FWidget*> Widgets = Widget->GetManagedWidgets();

		CreateDebuggersForWidgets(InVerticalBox, Widgets, Depth + 1);
	}
}
