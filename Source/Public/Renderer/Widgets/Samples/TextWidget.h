// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "../Widget.h"

class FTextWidget : public FWidget
{
public:
	FTextWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder = 0);
	virtual ~FTextWidget() override;

	void Render() override;

	void SetText(const std::string& InText);
	_NODISCARD std::string GetText() const;
	
	void SetWidgetSize(const FVector2D<int> InWidgetSize, const bool bUpdateAnchor = true) override;

protected:
	void AutoAdjustSize();
	void RecalculateSize() const;
	void RedrawText();
	void GetFont();

protected:
	std::string Text;
	int TextSize;

	FFont* Font;
	FFontAsset* FontAsset;
	
	SDL_Color TextColor;
	SDL_Rect* SDLRect;
	SDL_Texture* TextTexture;

	bool bAutoScaleWidget;
	
};
