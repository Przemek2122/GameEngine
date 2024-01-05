// Created by Przemys³aw Wiewióra 2020

#include "CoreEngine.h"
#include "Assets/TypesForAssets/Texture.h"
#include "SDL/SDL_image.h"

FTexture::FTexture(const std::string& InTexturePath, SDL_Renderer* Renderer)
{
	// Attempt load
	SDL_Surface* TemporarySurface = IMG_Load(InTexturePath.c_str());

	// Check if succesfuly loaded
	if (TemporarySurface != nullptr)
	{
		// To memory
		SDLTexture = SDL_CreateTextureFromSurface(Renderer, TemporarySurface);

		SDL_FreeSurface(TemporarySurface);
	}
}

FTexture::~FTexture()
{
	SDL_DestroyTexture(SDLTexture);
}

void FTexture::Draw(SDL_Renderer* Renderer, const SDL_Rect SourceRect, const SDL_Rect DestinationRect) const
{
	SDL_RenderCopy(Renderer, SDLTexture, &SourceRect, &DestinationRect);
}
