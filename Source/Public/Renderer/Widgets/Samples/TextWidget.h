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
	virtual ~FTextWidget() override;

	/** Begin FWidget */
	virtual void Render() override;
	virtual void SetWidgetLocationAbsolute(const FVector2D<int> InWidgetLocation) override;
	virtual void SetWidgetLocationRelative(const FVector2D<int> InWidgetLocation) override;
	virtual void SetWidgetSize(FVector2D<int> InWidgetSize, const bool bUpdateAnchor = true) override;
	virtual void OnClippingMethodChanged(EClipping NewClipping) override;
	/** End FWidget */
	
	void SetText(const std::string& InText);
	_NODISCARD std::string GetDesiredText() const;
	_NODISCARD std::string GetRenderedText() const;

protected:
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
	/** Returns font asset dependent on font and font size */
	void UpdateFont();

protected:
	std::string DesiredText;
	std::string RenderedText;
	int TextSize;

	FFont* Font;
	FFontAsset* FontAsset;
	
	FColorRGBA TextRenderColor;
	FColorRGBA TextBackgroundRenderColor;

	SDL_Rect* SDLRect;
	SDL_Texture* TextTexture;

	FVector2D<int> LastTextTextureSize;

public:
	void SetTextRenderMode(ETextRenderMode NewTextRenderMode);
	_NODISCARD ETextRenderMode GetTextRenderMode() const;

private:
	ETextRenderMode TextRenderMode;

protected:
	bool bAutoScaleWidget;
	
};
