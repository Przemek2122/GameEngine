// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "Assets/Font.h"
#include "Assets/FontAsset.h"

static const char* DefaultText = "Default text"; 
static const char* DefaultFont = "OpenSans"; 

FTextWidget::FTextWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, DesiredText(DefaultText)
	, RenderedText(DefaultText)
	, TextSize(16)
	, AssetsManager(Engine->GetAssetsManager())
	, FontAsset(AssetsManager->GetAsset<FFontAsset>(DefaultFont))
	, TextRenderColor(255)
	, TextBackgroundRenderColor({ 255, 0, 0})
	, SDLRect(new SDL_Rect)
	, TextTexture(nullptr)
	, LastTextTextureSize({ 0, 0 })
	, TextRenderMode(ETextRenderMode::Blended)
	, bAutoScaleWidget(true)
{
#if _DEBUG
	// Unable to find font asset.
	ENSURE_VALID(FontAsset != nullptr);
#endif
}

FTextWidget::~FTextWidget()
{
	SDL_free(TextTexture);
	delete SDLRect;
}

void FTextWidget::Init()
{
	FWidget::Init();

	RecalculateSize();

	if (FontAsset != nullptr)
	{
		SetText(DefaultText);
	}

	AutoAdjustSize(GetClippingMethod() == EClipping::Cut);
}

void FTextWidget::Render()
{
	SDL_RenderCopy(GetRenderer()->GetSDLRenderer(), TextTexture, nullptr, SDLRect);
}

void FTextWidget::SetWidgetLocation(const FVector2D<int> InWidgetLocation, EWidgetOrientation WidgetOrientation, const bool bSetNoneAnchor)
{
	FWidget::SetWidgetLocation(InWidgetLocation, WidgetOrientation, bSetNoneAnchor);

	RefreshTextWidget();
}

void FTextWidget::OnClippingMethodChanged(const EClipping NewClipping)
{
	Super::OnClippingMethodChanged(NewClipping);

	RefreshTextWidget();
}

void FTextWidget::RefreshWidget(const bool bRefreshChildren)
{
	Super::RefreshWidget(bRefreshChildren);

	RefreshTextWidget();
}

void FTextWidget::SetText(const std::string& InText)
{
	DesiredText = InText;

	AutoAdjustSize(GetClippingMethod() == EClipping::Cut);
	RefreshTextWidget();
}

std::string FTextWidget::GetDesiredText() const
{
	return DesiredText;
}

std::string FTextWidget::GetRenderedText() const
{
	return RenderedText;
}

void FTextWidget::AutoAdjustSize(const bool bLimitToParentSize)
{
	FVector2D<int> NewWidgetSize;

	if (bLimitToParentSize)
	{
		AutoAdjustTextSize(GetParent()->GetWidgetManagerSize());
	}
	else
	{
		RenderedText = DesiredText;
	}
	
	CalculateDefaultSizeForRenderText(NewWidgetSize);
	
	SetWidgetSize(NewWidgetSize);
}

void FTextWidget::AutoAdjustTextSize(const FVector2D<int>& InMaxSize)
{
	RenderedText = DesiredText;

	auto StringSize = RenderedText.length();

	FVector2D<int> OutSize(0);

	CalculateDefaultSizeForRenderText(OutSize);
	
	while(OutSize.X > InMaxSize.X)
	{
		CalculateDefaultSizeForRenderText(OutSize);
		
		if (OutSize.X > InMaxSize.X)
		{
			RenderedText = RenderedText.substr(0, --StringSize);
		}
		else
		{
			return;
		}
	}
}

int FTextWidget::CalculateDefaultSizeForRenderText(FVector2D<int>& InOutSize) const
{
	int ErrorState = -1;

	static TTF_Font* Font;
	if (!Font)
	Font = FontAsset->GetFont(TextSize)->GetFont();
	if (Font != nullptr)
	{
		ErrorState = TTF_SizeUTF8(Font, RenderedText.c_str(), &InOutSize.X, &InOutSize.Y);
	}
	
	if (ErrorState) 
	{
		LOG_ERROR("Text could not be rendered. TTF: '" << TTF_GetError() << "' SDL: '" << SDL_GetError() << "'");
	}

	return ErrorState;
}

void FTextWidget::RecalculateSize() const
{
	const FVector2D<int>& LocationCache = GetWidgetLocation(EWidgetOrientation::Absolute);
	const FVector2D<int>& SizeCache = GetWidgetSize();

	SDLRect->x = LocationCache.X;
	SDLRect->y = LocationCache.Y;
	SDLRect->w = SizeCache.X;
	SDLRect->h = SizeCache.Y;
}

void FTextWidget::RedrawText()
{
	if (FontAsset == nullptr)
	{
		// Without FontAsset it has no chance of working, font is required.
		ENSURE_VALID(false);

		return;
	}

	if (bAutoScaleWidget)
	{
		AutoAdjustSize(GetClippingMethod() == EClipping::Cut);
	}

	SDL_Surface* SdlSurface = nullptr;
	TTF_Font* Font = FontAsset->GetFont(TextSize)->GetFont();
	if (Font != nullptr)
	{
		switch (TextRenderMode)
		{
		case ETextRenderMode::Solid:
			{
				SdlSurface = TTF_RenderText_Solid(Font, RenderedText.c_str(), TextRenderColor);
			}
			break;
		case ETextRenderMode::Blended:
			{
				SdlSurface = TTF_RenderText_Blended(Font, RenderedText.c_str(), TextRenderColor);
			}
			break;
		case ETextRenderMode::Shaded:
			{
				SdlSurface = TTF_RenderText_Shaded(Font, RenderedText.c_str(), TextRenderColor, TextBackgroundRenderColor);
			}
			break;
		}
	}

	if (SdlSurface == nullptr)
	{
		// Unable to render text
		ENSURE_VALID(false);
		
		return;
	}
	
	SDL_LockSurface(SdlSurface); // Lock surface for safe pixel access
	
	FVector2D<int> WidgetSize = GetWidgetSize();

	// If we have texture and X or Y size has changed and we need texture of different size
	if (TextTexture == nullptr || (WidgetSize.X != LastTextTextureSize.X || WidgetSize.Y != LastTextTextureSize.Y))
	{
		// Destroy old texture
		SDL_free(TextTexture);

		// Create new texture
		TextTexture = SDL_CreateTextureFromSurface(GetRenderer()->GetSDLRenderer(), SdlSurface);
		
		LastTextTextureSize = GetWidgetSize();
	}
	else
	{
		// If size not changed update old texture
		SDL_UpdateTexture(TextTexture, nullptr, SdlSurface->pixels, SdlSurface->pitch);
	}
	
	SDL_FreeSurface(SdlSurface);
	SDL_QueryTexture(TextTexture, nullptr, nullptr, &WidgetSize.X, &WidgetSize.Y);
}

void FTextWidget::SetTextRenderMode(const ETextRenderMode NewTextRenderMode)
{
	TextRenderMode = NewTextRenderMode;
}

ETextRenderMode FTextWidget::GetTextRenderMode() const
{
	return TextRenderMode;
}

void FTextWidget::RefreshTextWidget()
{
	RecalculateSize();

	RedrawText();
}
