// Created by Przemys�aw Wiewi�ra 2020

#include "CoreEngine.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "Assets/TypesForAssets/Font.h"
#include "Assets/Assets/FontAsset.h"

static const char* DefaultText = "Default text"; 
static const char* DefaultFont = "OpenSans";

FTextWidget::FTextWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder)
	: FWidget(InWidgetManagementInterface, InWidgetName, InWidgetOrder)
	, DesiredText(DefaultText)
	, RenderedText(DefaultText)
	, TextSize(16)
	, AssetsManager(GEngine->GetAssetsManager())
	, FontAsset(AssetsManager->GetAsset<FFontAsset>(DefaultFont))
	, TextRenderColor(255)
	, TextBackgroundRenderColor({ 255, 0, 0})
	, SDLRect(new SDL_Rect)
	, TextTexture(nullptr)
	, LastTextTextureSize({ 0, 0 })
	, CurrentTextRenderMode(ETextRenderMode::None)
	, DesiredTextRenderMode(ETextRenderMode::Blended)
	, bAutoCutTextToFitInsideOfParent(false)
{
#if _DEBUG
	// Unable to find font asset.
	ENSURE_VALID(FontAsset != nullptr);
#endif

	SetWidgetMargin(FWidgetMargin(20, 16));
}

FTextWidget::~FTextWidget()
{
	SDL_DestroyTexture(TextTexture);

	delete SDLRect;
}

void FTextWidget::Render()
{
	SDL_RenderCopy(GetRenderer()->GetSDLRenderer(), TextTexture, nullptr, SDLRect);

	Super::Render();
}

void FTextWidget::OnClippingMethodChanged(const EClipping NewClipping)
{
	Super::OnClippingMethodChanged(NewClipping);

	// We need to redraw because it might need to cut part of text
	OnTextChanged();
}

void FTextWidget::UpdateWidgetLocation()
{
	Super::UpdateWidgetLocation();

	const FVector2D<int>& LocationCache = GetWidgetLocation(EWidgetOrientation::Absolute);

	SDLRect->x = LocationCache.X;
	SDLRect->y = LocationCache.Y;
}

void FTextWidget::UpdateWidgetSize()
{
	Super::UpdateWidgetSize();

	const FVector2D<int>& SizeCache = GetWidgetSize();

	SDLRect->w = SizeCache.X;
	SDLRect->h = SizeCache.Y;
}

void FTextWidget::UpdateAnchor()
{
	Super::UpdateAnchor();

	const FVector2D<int>& LocationCache = GetWidgetLocation(EWidgetOrientation::Absolute);
	const FVector2D<int>& SizeCache = GetWidgetSize();

	SDLRect->x = LocationCache.X;
	SDLRect->y = LocationCache.Y;
	SDLRect->w = SizeCache.X;
	SDLRect->h = SizeCache.Y;
}

void FTextWidget::SetText(const std::string& InText)
{
	DesiredText = InText;

	OnTextChanged();
}

std::string FTextWidget::GetDesiredText() const
{
	return DesiredText;
}

std::string FTextWidget::GetRenderedText() const
{
	return RenderedText;
}

void FTextWidget::RebuildWidget()
{
	Super::RebuildWidget();

	if (FontAsset != nullptr)
	{
		// Update text
		RedrawText();
	}
}

void FTextWidget::OnTextChanged()
{
	RequestWidgetRebuild();
}

void FTextWidget::AutoAdjustSize(const bool bLimitToParentSize)
{
	FVector2D<int> NewWidgetSize;

	if (bLimitToParentSize)
	{
		AutoAdjustTextSize(GetParent()->GetWidgetManagerSize());
	}
	
	CalculateDefaultSizeForRenderText(NewWidgetSize);
	
	SetWidgetSize(NewWidgetSize);
}

void FTextWidget::AutoAdjustTextSize(const FVector2D<int>& InMaxSize)
{
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
			break;
		}
	}
}

int FTextWidget::CalculateDefaultSizeForRenderText(FVector2D<int>& InOutSize) const
{
	int ErrorState = -1;

	static TTF_Font* Font;
	if (Font == nullptr)
	{
		Font = FontAsset->GetFont(TextSize)->GetFont();
	}
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

void FTextWidget::SetTextRenderMode(const ETextRenderMode NewTextRenderMode)
{
	DesiredTextRenderMode = NewTextRenderMode;

	// @TODO We could run single rebuild instead of rebuilding whole hierarchy as this change should not change size
	RequestWidgetRebuild();
}

ETextRenderMode FTextWidget::GetTextRenderMode() const
{
	return DesiredTextRenderMode;
}

void FTextWidget::RedrawText()
{
	const bool bIsInputDataCorrect = (FontAsset != nullptr && !DesiredText.empty());
	const bool bIsAnyDataChanged = (DesiredText != RenderedText || CurrentTextRenderMode != DesiredTextRenderMode);
	if (bIsInputDataCorrect && bIsAnyDataChanged)
	{
		RenderedText = DesiredText;

		if (bAutoCutTextToFitInsideOfParent)
		{
			AutoAdjustSize(GetClippingMethod() == EClipping::Cut);
		}

		SDL_Surface* SdlSurface = nullptr;
		TTF_Font* Font = FontAsset->GetFont(TextSize)->GetFont();
		if (Font != nullptr)
		{
			switch (DesiredTextRenderMode)
			{
				case ETextRenderMode::Solid:
				{
					SdlSurface = TTF_RenderText_Solid(Font, RenderedText.c_str(), TextRenderColor);

					break;
				}
				case ETextRenderMode::Blended:
				{
					SdlSurface = TTF_RenderText_Blended(Font, RenderedText.c_str(), TextRenderColor);

					break;
				}
				case ETextRenderMode::Shaded:
				{
					SdlSurface = TTF_RenderText_Shaded(Font, RenderedText.c_str(), TextRenderColor, TextBackgroundRenderColor);

					break;
				}
				default: ;
			}

			CurrentTextRenderMode = DesiredTextRenderMode;
		}
		else
		{
			LOG_ERROR("Font is NULL");
		}

		if (SdlSurface != nullptr)
		{
			SDL_LockSurface(SdlSurface); // Lock surface for safe pixel access

			FVector2D<int> WidgetSize = GetWidgetSize();

			// If we have texture and X or Y size has changed and we need texture of different size
			if (TextTexture == nullptr || (WidgetSize.X != LastTextTextureSize.X || WidgetSize.Y != LastTextTextureSize.Y))
			{
				// Destroy old texture
				SDL_DestroyTexture(TextTexture);

				// Create new texture
				TextTexture = SDL_CreateTextureFromSurface(GetRenderer()->GetSDLRenderer(), SdlSurface);

				LastTextTextureSize = GetWidgetSize();
			}
			else
			{
				// If size not changed update old texture
				int bWasUpdateTextureSuccess = SDL_UpdateTexture(TextTexture, nullptr, SdlSurface->pixels, SdlSurface->pitch);

				if (bWasUpdateTextureSuccess != 0)
				{
					LOG_ERROR("SDL_UpdateTexture error: " << SDL_GetError());
				}
			}

			SDL_UnlockSurface(SdlSurface);
			SDL_FreeSurface(SdlSurface);

			SDL_QueryTexture(TextTexture, nullptr, nullptr, &WidgetSize.X, &WidgetSize.Y);

			AutoAdjustSize();
		}
		else
		{
			LOG_ERROR("SdlSurface is NULL");
		}
	}
	else
	{
		if (FontAsset == nullptr)
		{
			LOG_ERROR("FontAsset for Text widget is null");
		}

		if (DesiredText.empty())
		{
			LOG_ERROR("Desired text is empty, if you intend to hide widget, use SetVisibility.");
		}
	}
}
