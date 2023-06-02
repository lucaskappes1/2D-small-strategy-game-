#include "Mouse.h"

Mouse::Mouse(SDL_Texture* tex, SDL_Renderer* renderer)
{
	mTexture = tex;
	mDestR = { 0, 0, 25, 25 };
	SDL_ShowCursor(false);
	mRenderer = renderer;
	mPoint = { 0, 0, 1, 1 };
}

void Mouse::Update()
{
	SDL_GetMouseState(&mDestR.x, &mDestR.y);
	mPoint.x = mDestR.x;
	mPoint.y = mDestR.y;
}

void Mouse::Draw()
{
	SDL_RenderCopy(mRenderer, mTexture, NULL, &mDestR);
}
