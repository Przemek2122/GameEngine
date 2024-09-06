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

	int32 SetHorizontal() const { return Horizontal; }
	int32 SetVertical() const { return Vertical; }

	FVector2D<int32> Get() const { return { Horizontal, Vertical }; }

	int32 GetHorizontal() const { return Horizontal; }
	int32 GetVertical() const { return Vertical; }

	int32 GetLeft() const { return Horizontal / 2; }
	int32 GetRight() const { return Horizontal / 2; }
	int32 GetTop() const { return Vertical / 2; }
	int32 GetBottom() const { return Vertical / 2; }

protected:
	int32 Horizontal;
	int32 Vertical;
};
