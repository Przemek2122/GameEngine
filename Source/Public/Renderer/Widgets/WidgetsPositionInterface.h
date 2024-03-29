// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"

#include "WidgetEnums.h"

/**
 * Class responsible for managing widget location and size.
 */
class IWidgetPositionInterface : public IWidgetManagementInterface
{
	friend FWidget;
	
public:
	IWidgetPositionInterface(IWidgetManagementInterface* InWidgetManagementInterface);
	~IWidgetPositionInterface() override = default;
	
	virtual void OnLocationChanged();
	virtual void OnSizeChanged();
	virtual void OnAnchorChanged(const EAnchor NewAnchor);

	_NODISCARD virtual FVector2D<int> GetWidgetLocation(EWidgetOrientation WidgetOrientation = EWidgetOrientation::Absolute) const;

	/** Set widget location on screen/n @bSetNoneAnchor set to true if you want to disable Anchors */
	virtual void SetWidgetLocation(const FVector2D<int> InWidgetLocation, EWidgetOrientation WidgetOrientation = EWidgetOrientation::Absolute, const bool bSetNoneAnchor = true);
	
	/** @returns size of this widget. */
	_NODISCARD virtual FVector2D<int> GetWidgetSize() const;

	/** Set size of this widget in pixels. */
	virtual void SetWidgetSize(const FVector2D<int> InWidgetSize);

	/** Set size of this widget in percentage of parent size (0.0 to 1.0) where 1.0 means 100% size. */
	virtual void SetWidgetSizePercent(const FVector2D<float> InScreenPercentage);

	void RefreshSizeInPercent();

	/** Called when parent changed size */
	void RefreshWidgetSize();

	/** Called when parent changed location */
	void RefreshWidgetLocation();

	void RefreshAnchor();
	void SetDefaultAnchor(const EAnchor NewAnchor);
	void SetAnchor(const EAnchor NewAnchor);
	_NODISCARD EAnchor GetAnchor() const;

	_NODISCARD EClipping GetClippingMethod() const;
	void SetClippingMethod(const EClipping NewClippingMethod);

	/** @Note: Called before setting ClippingMethod with NewClippingMethod */
	virtual void OnClippingMethodChanged(EClipping NewClippingMethod);

protected:
	virtual void OnRefreshWidgetSize();
	virtual void OnRefreshWidgetLocation();

	virtual void RefreshWidgetSizeChild();
	virtual void RefreshWidgetLocationChild();

private:
	/** Current widget location absolute */
	FVector2D<int> WidgetLocationInterface;

	/** Type of size of widgets. Pixels or Screen percentage */
	EWidgetSizeType WidgetSizeType;

	/** Size of this widget in pixels */
	FVector2D<int> WidgetSizeInPixelsInterface;

	/** Size of this widget in screen percentage */
	FVector2D<float> WidgetSizeInScreenPercentInterface;

	/** Default anchor when this widget is created.\n @See Init() */
	EAnchor DefaultAnchorInterface;
	/** Anchor of this widget. Used to align to parent. */
	EAnchor AnchorInterface;

	/** Defines widget behavior if it's too big. */
	EClipping ClippingMethodInterface;
	
};
