// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "../Widget.h"

/** What should happen if widget is too big? */
enum class ETextRenderMode : Uint8
{
	Solid,						// Render text only
	Shaded,						// Render text with background
	Blended,					// Render
};

class FTextWidget : public FWidget
{
public:
	FTextWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder = 0);
	~FTextWidget() override;
	
	/** Begin FWidget */
	void Init() override;
	void Render() override;
	void SetWidgetLocation(const FVector2D<int> InWidgetLocation, EWidgetOrientation WidgetOrientation, const bool bSetNoneAnchor) override;
	void OnClippingMethodChanged(EClipping NewClipping) override;
	void RefreshWidget(const bool bRefreshChildren) override;
	/** End FWidget */

public:
	/** Use for advanced text with parameters like InText='"Test button " << 1' */
#define SET_TEXT_ADV(InText) SetText(TEXT_ADV(InText))
	/**
	 * Use for simple string InText='"Some text ..."'
	 * You can use SetTextM("Test button " << 1 << SomeParameter)
	 * or std::format("{1} to {0}", "a", "b") for parameterized versions.
	 */
	void SetText(const std::string& InText);

	_NODISCARD std::string GetDesiredText() const;
	_NODISCARD std::string GetRenderedText() const;

	void SetTextRenderMode(ETextRenderMode NewTextRenderMode);
	_NODISCARD ETextRenderMode GetTextRenderMode() const;

protected:
	void RefreshTextWidget();

	/** Auto adjusts size for @RenderedText */
	void AutoAdjustSize(const bool bLimitToParentSize = false);
	/** Helper for AutoAdjustSize */
	virtual void AutoAdjustTextSize(const FVector2D<int>& InMaxSize);
	/** SDL Wrapper */
	int CalculateDefaultSizeForRenderText(FVector2D<int>& InOutSize) const;
	/** Calculate size for SDL */
	void RecalculateSize() const;
	/** Makes new texture for text */
	void RedrawText();

protected:
	std::string DesiredText;
	std::string RenderedText;

	int TextSize;

	FAssetsManager* AssetsManager;
	FFontAsset* FontAsset;
	
	FColorRGBA TextRenderColor;
	FColorRGBA TextBackgroundRenderColor;

	SDL_Rect* SDLRect;
	SDL_Texture* TextTexture;

	FVector2D<int> LastTextTextureSize;

	ETextRenderMode TextRenderMode;

protected:
	bool bAutoScaleWidget;
	
};
