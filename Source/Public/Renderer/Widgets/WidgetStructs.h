#pragma once

/** Structure for generating parent widget using children */
struct FWidgetGeometry
{
	/** Widget size */
	FVector2D<int32> Size;
};

struct FWidgetMargin
{
	/** Will set given padding to all 4 sides */
	FWidgetMargin(const int32 Margin)
		: Horizontal(Margin)
		, Vertical(Margin)
	{
	}

	FWidgetMargin(const int32 InHorizontalMargin = 0, const int32 InVerticalMargin = 0)
		: Horizontal(InHorizontalMargin)
		, Vertical(InVerticalMargin)
	{
	}

	FVector2D<int32> GetSize() const { return { Horizontal, Vertical }; }

	int32 Horizontal;
	int32 Vertical;
};
