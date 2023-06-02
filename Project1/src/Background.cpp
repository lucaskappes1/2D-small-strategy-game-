#include "Background.h"

Background::Background(SDL_Texture* texture, SDL_Renderer* renderer)
{
	mTexture = texture;
	mDestR = { 0, 0, 800, 600 };
	mRenderer = renderer;
}

void Background::Draw()
{
	SDL_RenderCopy(mRenderer, mTexture, NULL, &mDestR);
}

