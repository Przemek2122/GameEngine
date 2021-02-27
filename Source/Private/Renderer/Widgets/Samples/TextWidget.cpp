// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "Assets/Font.h"
#include "Assets/FontAsset.h"

FTextWidget::FTextWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, Text("Sample text")
	, TextSize(16)
	, Font(nullptr)
	, SDLRect(new SDL_Rect)
	, TextTexture(nullptr)
	, bAutoScaleWidget(true)
{
	FontAsset = Engine->GetAssetsManager()->GetAsset<FFontAsset>("OpenSans");

#if _DEBUG
	// Unable to find font asset.
	ENSURE_VALID(FontAsset != nullptr);
#endif
	
	TextColor.r = 255;
	TextColor.g = 255;
	TextColor.b = 255;
	TextColor.a = 255;

	GetFont();

	SetText("Default text.");
}

FTextWidget::~FTextWidget()
{
	SDL_free(TextTexture);
	delete SDLRect;
}

void FTextWidget::Render()
{
	SDL_RenderCopy(GetRenderer()->GetSDLRenderer(), TextTexture, nullptr, SDLRect);
}

void FTextWidget::SetText(const std::string& InText)
{
	Text = InText;

	RedrawText();

	if (bAutoScaleWidget)
	{
		AutoAdjustSize();
	}
}

std::string FTextWidget::GetText() const
{
	return Text;
}

void FTextWidget::SetWidgetSize(const FVector2D<int> InWidgetSize, const bool bUpdateAnchor)
{	
	Super::SetWidgetSize(InWidgetSize);

	RecalculateSize();

	UpdateAnchor();
}

void FTextWidget::AutoAdjustSize()
{
	if (Font == nullptr)
	{
		return;
	}
	
	FVector2D<int> NewWidgetSize;

	if(TTF_SizeUTF8(Font->GetFont(), Text.c_str(), &NewWidgetSize.X, &NewWidgetSize.Y)) 
	{
		LOG_ERROR("Text could not be rendered. " << TTF_GetError());
	}
	
	SetWidgetSize(NewWidgetSize);
}

void FTextWidget::RecalculateSize() const
{
	SDLRect->x = GetWidgetLocationAbsolute().X;
	SDLRect->y = GetWidgetLocationAbsolute().Y;
	SDLRect->w = GetWidgetSize().X;
	SDLRect->h = GetWidgetSize().Y;
}

void FTextWidget::RedrawText()
{
	if (Font == nullptr)
	{
		return;
	}
	
	FVector2D<int> WidgetSize = GetWidgetSize();
	
	SDL_Surface* SdlSurface = TTF_RenderText_Blended(Font->GetFont(), Text.c_str(), TextColor);
	SDL_LockSurface(SdlSurface); // Lock surface for safe pixel access

	if (TextTexture != nullptr && WidgetSize.X != SdlSurface->w || WidgetSize.Y != SdlSurface->h) 
	{
		// Destroy old texture
		SDL_free(TextTexture);

		// Create new texture
		TextTexture = SDL_CreateTextureFromSurface(GetRenderer()->GetSDLRenderer(), SdlSurface);
	}
	else
	{
		// If size not changed update old texture
		SDL_UpdateTexture(TextTexture, nullptr, SdlSurface->pixels, SdlSurface->pitch);
	}
	
	SDL_FreeSurface(SdlSurface);
	SDL_QueryTexture(TextTexture, nullptr, nullptr, &WidgetSize.X, &WidgetSize.Y);

	AutoAdjustSize();
}

void FTextWidget::GetFont()
{
	Font = Engine->GetAssetsManager()->GetFont(FontAsset, TextSize);	
}
