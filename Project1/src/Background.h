#pragma once
#include "units/GameObject.h"
#include "SDL.h"

class Background
{
public:
	Background(SDL_Texture* texture, SDL_Renderer* renderer, int width, int height);
	void Draw();
private:
	SDL_Rect mDestR;
	SDL_Texture* mTexture;
	SDL_Renderer* mRenderer;
};

