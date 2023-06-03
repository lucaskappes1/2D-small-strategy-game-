#include "Background.h"

Background::Background(SDL_Texture* texture, SDL_Renderer* renderer, int width, int height)
{
	mTexture = texture;
	mDestR = { 0, 0, width, height };
	mRenderer = renderer;
}

void Background::Draw()
{
	SDL_RenderCopy(mRenderer, mTexture, NULL, &mDestR);
}

