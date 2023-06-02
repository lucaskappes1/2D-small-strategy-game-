#include "Button.h"

Button::Button(SDL_Texture* tex, SDL_Renderer* renderer, Mouse* mouse, int xpos, int ypos, SDL_Rect srcR, TTF_Font* Font)
{
	mTexture = tex;
	mRenderer = renderer;
	mMouse = mouse;
	mDestR = { xpos, ypos, 50, 50 };
	mSrcR = srcR;
	mIsSelected = false;
	mFont = Font;
}

Button::~Button()
{
	delete mTooltip;
}

void Button::Update()
{
	if (SDL_HasIntersection(&mDestR, &mMouse->getCollisionRect()))
	{
		mIsSelected = true;
		//display text
	}
	else
	{
		mIsSelected = false;
	}
}

void Button::Draw()
{
	SDL_RenderCopy(mRenderer, mTexture, &mSrcR, &mDestR);
	if (mIsSelected)
	{
		SDL_RenderCopy(mRenderer, mTextTexture, NULL, &mTextRect);
	}
}

void Button::addTooltip(const char* Tooltip)
{
	mTooltip = new std::string(Tooltip);
	mTextSurface = TTF_RenderText_Solid(mFont, mTooltip->c_str(), mTextColor);
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mTextSurface);
	mTextRect = { 50, 150, 500, 20 };
}
