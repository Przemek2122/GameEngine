// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

class FTexture
{
public:
	FTexture(const std::string& InTexturePath, SDL_Renderer* Renderer);
	~FTexture();

	void Draw(SDL_Renderer* Renderer, SDL_Rect SourceRect, SDL_Rect DestinationRect) const;

protected:
	SDL_Texture* SDLTexture;
	
};
